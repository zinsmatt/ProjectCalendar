#include "jourgraphicscene.h"


QGraphicsRectItem* JourGraphicScene::ajouterEvenement(const QString &titre, const QTime &deb,
                                                      const Duree &dur, Evenement*e, const QColor& coul_fond, const QColor& coul_contour)
{

    // affichage du rectangle
    int mins_ecoulees = -deb.secsTo(QTime(6,0)) / 60;
    QTime fin = deb;
    fin = fin.addSecs(dur.getDureeEnMinutes() * 60);

    qreal y = ( hauteur / nb_minutes ) * mins_ecoulees;
    qreal h = ( hauteur / nb_minutes ) * dur.getDureeEnHeures()*60;

    EvenementGraphicItem *tache = new EvenementGraphicItem(-2,y-1,largeur+3,h+1,e);
    tache->setPen(QPen(coul_contour));
    tache->setBrush(QBrush(coul_fond));
    QGraphicsScene::addItem(tache);
    tache->setFlag(QGraphicsItem::ItemIsSelectable);
    tache->setZValue(1);


    // affichage du texte dans le rectangle
    int Xtxt = 0,Ytxt = y;
    QString s;
    if(dur.getDureeEnMinutes()<30)
        return 0;
    else if(dur.getDureeEnMinutes()<75)
    {
        Xtxt = -3;
        Ytxt = y - 3;
        s = deb.toString("hh:mm") + "   -   " + fin.toString("hh:mm");
    }else if(dur.getDureeEnMinutes() >= 75)
        s = deb.toString("hh:mm") + "   -   " + fin.toString("hh:mm") + "\n" + titre;
    else
        s = deb.toString("hh:mm") + "   -   " + fin.toString("hh:mm");

    QGraphicsTextItem *txt = QGraphicsScene::addText(s,QFont("Helvetica",8));
    txt->setDefaultTextColor(QColor("black"));
    txt->setTextWidth(95);
    txt->setX(Xtxt);
    txt->setY(Ytxt);
    txt->setZValue(2);

    return tache;
}

void JourGraphicScene::dessinerFond()
{
    //dessine le quadrillages des heures sur le fond de la scene
    qreal r = (hauteur / nb_minutes) * 30;
    qreal x = r;
    int i=1;
    while( x < 480)
    {
        if(i%2==0)
            QGraphicsScene::addLine(-5,x,105,x,QPen(QColor("gray"),1,Qt::PenStyle(Qt::DashLine)))->setZValue(0);
        else
            QGraphicsScene::addLine(-5,x,105,x,QPen(QColor("lightGray"),1,Qt::PenStyle(Qt::DashDotLine)))->setZValue(0);

        x += r;
        i++;
    }
}


void JourGraphicScene::removeAllItems(){
    //vide la scene
    QList<QGraphicsItem*> itemsList = this->items();
    QList<QGraphicsItem*>::iterator iter = itemsList.begin();
    QList<QGraphicsItem*>::iterator end = itemsList.end();
    while(iter != end){
        QGraphicsItem* item = (*iter);
        this->removeItem(item); iter++;
    }
}


void JourGraphicScene::mise_a_jour()
{

    removeAllItems();
    dessinerFond();
    Agenda& ag = Agenda::getInstance();
    int i = 0;
    //reconstruction entiere de la scene
    for(Agenda::iterator it = ag.begin() ; it != ag.end() ; ++it)
    {
        QColor fond;
        if((*it).isProgrammationPartieTache())
            fond = QColor("orange") ;
        else if((*it).isRdv())
            fond = QColor("yellow");
        else if((*it).isProgrammationTache())
            fond = QColor("green");
        else if((*it).isEvenement1j())
            fond = QColor("red") ;
        else if((*it).isEvenementPj())
            fond = QColor("blue") ;

        if(!(*it).isEvenementPj() && (*it).getDate() == date)
        { //ajout d'un evenement sur 1 jour
            ajouterEvenement((*it).getSujet(),(*it).getHoraire(),(*it).getDuree(),&(*it),fond);

        }else if((*it).isEvenementPj())
        { // ajout d'un evnement sur plusieurs jours
            EvenementPj *evt = dynamic_cast<EvenementPj*>(&(*it));
            QDate deb = evt->getDate(), fin = evt->getDateFin();
            if(date == deb)
            {
                int nb_mins = evt->getHoraire().secsTo(QTime(22,0)) / 60;
                ajouterEvenement(evt->getSujet(),evt->getHoraire(),Duree(nb_mins),evt,fond);
            }else if(date<fin && date>deb)
            {
                ajouterEvenement(evt->getSujet(),QTime(6,0),Duree(960),evt,fond);
            }else if(date == fin)
            {
                int nb_mins = QTime(6,0).secsTo(evt->getHoraireFin()) / 60;
                ajouterEvenement(evt->getSujet(),QTime(6,0),Duree(nb_mins),evt,fond);
            }
        }
    }
}

