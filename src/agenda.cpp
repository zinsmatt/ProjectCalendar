#include "agenda.h"

Agenda* Agenda::instance = 0;

Agenda& Agenda::operator<<(Evenement& evt)
{
    for(std::vector<Evenement*>::iterator it = events.begin() ; it != events.end() ; ++it)
        if( *it == &evt)
            throw CalendarException("Erreur, Agenda, cet evenement existe deja");
    events.push_back(evt.clone());
    Observable::notifier();
    return *this;
}


Agenda& Agenda::operator>>(Evenement *evt)
{
    for(std::vector<Evenement*>::iterator it = events.begin() ; it != events.end() ; ++it)
        if( *it == evt){
            std::cout << "Agende :::: suppression evt "<<evt->getDate().toString().toStdString()<<" - "<<evt->getHoraire().toString().toStdString() <<"\n";
            delete evt;
            events.erase(it);
            Observable::notifier();
            return *this;
        }
    throw CalendarException("Erreur, Agenda, cet evenement n'existe pas");
}


Agenda::~Agenda()
{
    for(std::vector<Evenement*>::iterator it = events.begin() ; it != events.end() ; ++it)
        delete *it;
}

std::vector<ProgrammationTache*> Agenda::getProgrammationTache(const Tache* t)
{
    std::vector<ProgrammationTache*> tab;
    for(iterator it = begin() ; it != end() ; ++it)
    {
        if((*it).isProgrammationTache())
        {
            ProgrammationTache* prog = dynamic_cast<ProgrammationTache*>(&(*it));
            if( prog->getTache() == t)
                tab.push_back(prog);

        }
    }
    return tab;
}
