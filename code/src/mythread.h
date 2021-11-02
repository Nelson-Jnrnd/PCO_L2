#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <pcosynchro/pcothread.h>
#include <pcosynchro/pcomutex.h>
#include <QCryptographicHash>
#include <QVector>
#include <QString>

class PasswordCracker
{
public:
    // Constructeurs et Destructeurs...
    PasswordCracker(QString charset, QString salt, QString hash,
                    unsigned nbChars);
    PasswordCracker(QString charset, QString salt, QString hash,
                    unsigned nbChars, void (*_callbackOnCompletion)(PasswordCracker*));
    ~PasswordCracker();

    // Méthodes...

    // Lance nbThreads thread(s) pour chercher le mot de passe fourni au passwordCracker
    void StartCracking(unsigned nbThreads);
    // Retourne la valeur du mot de passe trouvé, retourne NULL si la recherche n'est pas terminée
    // ou si le mot de passe n'a pas pu être cracké.

    // Propriétés....

    QString getPasswordFound() const;
    // Retourne le pourcentage des combinaisons possibles essayées
    float getProgress();
    // Retourne le nombre des combinaisons possible du charset fourni
    unsigned long long getNbToCompute() const;
    // Retourne le nombre des combinaisons qui ont déjà été essayées
    unsigned long long getNbComputed() const;

    bool getIsReseachFinished() const;

private:
    // Champs...

    // Les threads qui travaillent à la recherche du mot de passe
    QVector<PcoThread*> _threads;
    // Chaine de caractères qui contient tous les caractères possibles du mot de passe
    QString _charset;
    // Le sel à concaténer au début du mot de passe avant de le hasher
    QString _salt;
    // Le hash dont on doit retrouver la préimage
    QString _hash;
    // Nombre de threads qui ont fini leur travail
    int _nbThreadsFinished;
    // Le nombre de caractères dans le mot de passe
    unsigned _nbChars;
    // Le nombre des combinaisons possible du charset fourni
    long long unsigned _nbToCompute;
    // Le nombre des combinaisons qui ont déjà été essayées
    long long unsigned _nbComputed;
    // La fonction callback à appeler quand la recherche du mot de passe est terminée
    void (*_onCompletion)(PasswordCracker*);
    // Le vérou pour protéger la variable partagée _nbComputed
    PcoMutex _nbComputedMutex = PcoMutex();
    // Le vérou pour protéger la procédure de fin de la recherche.
    // Pour éviter d'appeler la fonction de callback plusieurs fois
    PcoMutex _resultMutex = PcoMutex();
    // Mot de passe trouvé après la recherche brute force
    // NULL si le mot de passe n'est pas trouvé ou pas encore trouvé
    QString _passwordFound;
    // Statue de la recherche du mot de passe
    bool _isReseachFinished;

    // Méthodes...

    // Fonction qui exécute réélement la recherche du mot de passe
    QString passwordResearchLoop(unsigned id, QString currentPasswordString, QVector<unsigned int> currentPasswordArray, unsigned nbToCompute);
    // Fonction appelée à la création de chacun de thread, prépare les threads à la recherche puis appel la méthode passwordResearchLoop
    static void initializePasswordResearch(unsigned id, unsigned startingChar, unsigned nbToCompute, PasswordCracker* pwdc);
};
#endif // MYTHREAD_H
