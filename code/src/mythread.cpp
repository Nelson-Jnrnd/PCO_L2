#include "mythread.h"
#include <iostream>

/*
 * std::pow pour les long long unsigned int
 */
static long long unsigned int intPow (
        long long unsigned int number,
        long long unsigned int index)
{
    long long unsigned int i;

    if (index == 0)
        return 1;

    long long unsigned int num = number;

    for (i = 1; i < index; i++)
        number *= num;

    return number;
}

PasswordCracker::PasswordCracker(QString charset, QString salt, QString hash,
                                 unsigned nbChars) :PasswordCracker::PasswordCracker(charset, salt, hash,
                                                                                     nbChars, NULL){}

PasswordCracker::PasswordCracker(QString charset, QString salt, QString hash, unsigned nbChars, void (*_callbackOnCompletion)(PasswordCracker *))
{
    _charset = charset;
    _salt = salt;
    _hash = hash;
    _nbChars = nbChars;
    _nbToCompute = intPow(_charset.length(), _nbChars);
    _nbComputed = 0;
    _onCompletion = _callbackOnCompletion;
    _isReseachFinished = false;
    _nbThreadsFinished = 0;
}

QString PasswordCracker::getPasswordFound() const
{
    return _passwordFound;
}

float PasswordCracker::getProgress()
{
    return _nbComputed / _nbToCompute;
}

PasswordCracker::~PasswordCracker()
{
    // On attend demande a tout les threads d'arreter la recherche avant de détruire this
    for(PcoThread* t : _threads){
        t->requestStop();
    }
    for(PcoThread* t : _threads){
        t->join();
    }
}

unsigned long long PasswordCracker::getNbToCompute() const
{
    return _nbToCompute;
}

unsigned long long PasswordCracker::getNbComputed() const
{
    return _nbComputed;
}

bool PasswordCracker::getIsReseachFinished() const
{
    return _isReseachFinished;
}

QString PasswordCracker::passwordResearchLoop(unsigned id, QString currentPasswordString, QVector<unsigned int> currentPasswordArray, unsigned nbToCompute)
{
    unsigned long long nbComputed = 0;
    unsigned int i;
    unsigned int nbValidChars = _charset.length();
    /*
     * Hash du mot de passe à tester courant
     */
    QString currentHash;

    /*
     * Object QCryptographicHash servant à générer des md5
     */
    QCryptographicHash md5(QCryptographicHash::Md5);

    /*
     * Tant qu'on a pas tout essayé...
     */
    while (nbComputed < nbToCompute && !_isReseachFinished && !PcoThread::thisThread()->stopRequested()) {
        /* On vide les données déjà ajoutées au générateur */
        md5.reset();
        /* On préfixe le mot de passe avec le sel */
        md5.addData(_salt.toLatin1());
        md5.addData(currentPasswordString.toLatin1());
        /* On calcul le hash */
        currentHash = md5.result().toHex();
        /*
         * Si on a trouvé, on retourne le mot de passe courant (sans le sel)
         */
        if (currentHash == _hash)
            return currentPasswordString;

        /*
         * On récupère le mot de pass à tester suivant.
         *
         * L'opération se résume à incrémenter currentPasswordArray comme si
         * chaque élément de ce vecteur représentait un digit d'un nombre en
         * base nbValidChars.
         *
         * Le digit de poids faible étant en position 0
         */
        i = 0;

        while (i < (unsigned int)currentPasswordArray.size()) {
            currentPasswordArray[i]++;

            if (currentPasswordArray[i] >= nbValidChars) {
                currentPasswordArray[i] = 0;
                i++;
            } else
                break;
        }
        /*
         * On traduit les index présents dans currentPasswordArray en
         * caractères
         */
        for (i=0;i<_nbChars;i++)
            currentPasswordString[i]  = _charset.at(currentPasswordArray.at(i));

        nbComputed++;
        _nbComputedMutex.lock();
        _nbComputed++;
        _nbComputedMutex.unlock();
    }
    std::cout << "Pas trouvé :( thread " << id << " : " << nbComputed << " sur " << nbToCompute << std::endl;
    return NULL;
}

void PasswordCracker::StartCracking(unsigned nbThreads){
    _isReseachFinished = false;
    _nbThreadsFinished = 0;
    _threads = QVector<PcoThread*>(nbThreads);

    // Calcule le nombre de combinaisons à calculer par thread
    unsigned nbToComputeForThread = _nbToCompute / nbThreads;

    // Calcul du reste
    unsigned remainder = _nbToCompute % nbThreads;

    // Crée les threads selon le nombre demandé
    for(unsigned i = 0; i < nbThreads; ++i) {
        unsigned startingchar = _charset.length()/nbThreads * i;
        // Combinaisons pour ce thread
        unsigned nbToComputeCurrentThread = nbToComputeForThread;

        if(remainder > 0) {
            nbToComputeCurrentThread++;
            remainder--;
        }
        _threads[i] = new PcoThread(initializePasswordResearch, i, startingchar, nbToComputeCurrentThread, this);
    }
}

void PasswordCracker::initializePasswordResearch(unsigned id, unsigned startingChar, unsigned nbToCompute, PasswordCracker* pwdc) {

    /*
     * Mot de passe à tester courant
     */
    QString currentPasswordString;

    /*
     * Tableau contenant les index dans la chaine charset des caractères de
     * currentPasswordString
     */
    QVector<unsigned int> currentPasswordArray;

    /*
     * On initialise le premier mot de passe à tester courant en le remplissant
     * de nbChars fois du premier caractère de charset
     */
    currentPasswordString.fill(pwdc->_charset.at(startingChar),pwdc->_nbChars);
    currentPasswordArray.fill(startingChar,pwdc->_nbChars);

    QString result = pwdc->passwordResearchLoop(id, currentPasswordString, currentPasswordArray, nbToCompute);
    pwdc->_resultMutex.lock();
    pwdc->_nbThreadsFinished++;

    // Si la recherche est déjà marquée comme terminée la callback a déjà été appelée
    if(!pwdc->_isReseachFinished){
        // On appèle la callback uniquement si on est le thread qui a trouver la solution
        // ou alors si on est le dernier thread (et que les autres n'ont donc rien trouvé aussi)
        if((result.isNull() and pwdc->_nbThreadsFinished == pwdc->_threads.length()) or !result.isNull()){
            if(!result.isNull())
                pwdc->_passwordFound = result;
            pwdc->_isReseachFinished = true;
            std::cout << "trouvé !!! :) thread " << id << " : " << pwdc->_passwordFound.toStdString() << std::endl;
            if(pwdc->_onCompletion)
                pwdc->_onCompletion(pwdc);
        }
    }
    pwdc->_resultMutex.unlock();
}
