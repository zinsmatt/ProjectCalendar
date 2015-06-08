#ifndef PRECEDENCEMANAGER_H
#define PRECEDENCEMANAGER_H

#include <vector>
#include "precedence.h"
#include "exception.h"
#include "observateur.h"

/* on suppose que les precedences ne peuvent jamais être modif
 * elles seront soit suppr soit creeer
 * */

class PrecedenceManager : public Observable
{
    std::vector<Precedence*> precedences;
    static PrecedenceManager* instance;
    PrecedenceManager() {};
    PrecedenceManager(const PrecedenceManager&);
    PrecedenceManager& operator=(const PrecedenceManager&);
    ~PrecedenceManager() {}
    QString file;
public:
    static PrecedenceManager& getInstance();
    static void libereInstace();
    std::vector<Precedence*>::iterator findPrecedence(const Tache& t1, const Tache& t2);
    void ajouterPrecedence(const Tache &t1, const Tache &t2,const QString& nomProj);
    void retirerPrecedence(const Tache &t1, const Tache &t2);

    void save(const QString& f);
    void load(const QString& f);

    class iterator
    {
        friend class PrecedenceManager;
        std::vector<Precedence*>::iterator it;
        iterator(std::vector<Precedence*>::iterator i) : it(i) {}
    public:
        const Precedence& operator*() { return *(*it); }
        iterator& operator++() { ++it; return *this; }
        bool operator!=(const iterator& at) const { return it != at.it; }
    };

    iterator begin() { return iterator(precedences.begin()); }
    iterator end() { return iterator(precedences.end()); }

};

#endif // PRECEDENCEMANAGER_H