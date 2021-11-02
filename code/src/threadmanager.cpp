#include <QCryptographicHash>
#include <QVector>
#include <pcosynchro/pcothread.h>

#include "threadmanager.h"
#include "mythread.h"

#include <iostream>

/*
 * std::pow pour les long long unsigned int
 */
long long unsigned int intPow (
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

ThreadManager::ThreadManager(QObject *parent) :
    QObject(parent)
{}


void ThreadManager::incrementPercentComputed(double percentComputed)
{
    emit sig_incrementPercentComputed(percentComputed);
}

void onHackingComplete(PasswordCracker* pwdc){
    if(pwdc)
        std::cout << "exemple of callback " << pwdc->getPasswordFound().toStdString() << std::endl;
}

/*
 * Les paramètres sont les suivants:
 *
 * - charset:   QString contenant tous les caractères possibles du mot de passe
 * - salt:      le sel à concaténer au début du mot de passe avant de le hasher
 * - hash:      le hash dont on doit retrouver la préimage
 * - nbChars:   le nombre de caractères du mot de passe à bruteforcer
 * - nbThreads: le nombre de threads à lancer
 *
 * Cette fonction doit retourner le mot de passe correspondant au hash, ou une
 * chaine vide si non trouvé.
 */
QString ThreadManager::startHacking(
        QString charset,
        QString salt,
        QString hash,
        unsigned int nbChars,
        unsigned int nbThreads
)
{
    PasswordCracker pwdc = PasswordCracker(charset, salt, hash, nbChars, onHackingComplete);
    pwdc.StartCracking(nbThreads);


    while(true){
        if((pwdc.getNbComputed() % 10000) == 0){
            incrementPercentComputed((double) 10000 / pwdc.getNbToCompute());
        }
        if(pwdc.getIsReseachFinished()){
            if(pwdc.getPasswordFound().isNull())
                return QString("");
            std::cout << "---------------------------trouvé" << std::endl;
            return pwdc.getPasswordFound();
        }
    }

    /*
     * Si on arrive ici, cela signifie que tous les mot de passe possibles ont
     * été testés, et qu'aucun n'est la préimage de ce hash.
     */
    return QString("");
}
