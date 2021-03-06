#include "ajoutprecedencedialog.h"
#include "ui_ajoutprecedencedialog.h"
#include <QMessageBox>

AjoutPrecedenceDialog::AjoutPrecedenceDialog(Tache* t, Projet* p, QWidget *parent) :
    QDialog(parent),tache(t), projet(p),
    ui(new Ui::AjoutPrecedenceDialog)
{
    ui->setupUi(this);

    std::map<QString, Tache*> *map = projet->getTacheMap(tache->getId());

    //recherche des taches pouvant respecter la contrainte  et ajout dans le selecteur
    for(std::map<QString,Tache*>::iterator it = map->begin(); it != map->end() ; ++it )
    {
        if(it->second != tache ){
            bool ok = true;
            for(Tache::const_succ_iterator succIter = it->second->beginSucc() ; succIter != it->second->endSucc() ; ++succIter)
                if( *succIter == tache)
                    ok = false;
            if(ok){                
                ui->selecteur_tache_pred->addItem(it->second->getId());
            }
        }
    }
}

AjoutPrecedenceDialog::~AjoutPrecedenceDialog()
{
    delete ui;
}

void AjoutPrecedenceDialog::accept()
{
    if(ui->selecteur_tache_pred->currentText()!="")
    {
        Tache* pred = projet->getTache(ui->selecteur_tache_pred->currentText());
        Tache* succ = tache;
        ajouterPrecedenceRecurs(succ,pred);
    }
    done(1);
}



void AjoutPrecedenceDialog::ajouterPrecedenceRecurs(Tache* t,Tache* pred) //double recurs pour ajouter tous les preds a tous les succs
{
    // ajout recursive de la contrainte de precedence dans toutes les sous-taches
    ajouterPredRecurs(t,pred);
    if(t->isComposite()){
        TacheComposite *tc = dynamic_cast<TacheComposite*>(t);
        for(TacheComposite::iterator it = tc->begin(); it != tc->end() ; ++it)
            ajouterPrecedenceRecurs(&(*it),pred);
    }
}

void AjoutPrecedenceDialog::ajouterPredRecurs(Tache*t, Tache*pred)
{
    // ajout recursive de la contrainte de precedence dans toutes les sous-taches
    try{
        PrecedenceManager::getInstance().ajouterPrecedence(*pred,*t,projet);
    }catch(CalendarException e)
    {
        QMessageBox::warning(this,"Avertissement",e.getInfo());
    }

    if(pred->isComposite()){
        TacheComposite *tc = dynamic_cast<TacheComposite*>(pred);
        for(TacheComposite::iterator it = tc->begin() ; it!= tc->end() ; ++it)
            ajouterPredRecurs(t,&(*it));
    }
}
