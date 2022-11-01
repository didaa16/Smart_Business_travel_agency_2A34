#include "voyages.h"
#include "QMessageBox"
#include <QSqlQuery>
#include <QDebug>
#include<QSqlError>
#include <QObject>
Voyages::Voyages()
{
    ID=0;
    DESTINATION="";
    HOTEL="";
    PRIX=0;
}

    Voyages::Voyages(int ID,QString DESTINATION,QString HOTEL,float PRIX)
    {
        this->ID=ID;
        this->DESTINATION=DESTINATION;
        this->HOTEL=HOTEL;
        this->PRIX=PRIX;

    }

    int Voyages::getid(){return ID;}
    QString Voyages::getdestination(){return DESTINATION;}
    QString Voyages::hotel(){return HOTEL;}
    float Voyages::getprix(){return PRIX;}
    void Voyages::setid(int ID){this->ID=ID;}
    void Voyages::setdestination(QString DESTINATION){this->DESTINATION=DESTINATION;}
    void Voyages::sethotel(QString HOTEL){this->HOTEL=HOTEL;}
    void Voyages::setprix(float PRIX){this->PRIX=PRIX;}
    bool Voyages::ajouter()
{

QString id_string=QString::number(ID);
QString prix_string=QString::number(PRIX);

QSqlQuery query;

              query.prepare("INSERT INTO voyages (ID,DESTINATION,HOTEL,PRIX) "
                            "VALUES (:ID, :DEST, :HOTEL, :PRIX)");
              query.bindValue(":ID", id_string);
              query.bindValue(":DEST", DESTINATION);
              query.bindValue(":HOTEL", HOTEL);
              query.bindValue(":PRIX", prix_string);
              qDebug()<<query.lastError();
        return query.exec();


    }

    bool Voyages::supprimer(int ID){
        QSqlQuery query;
        query.prepare("Delete from voyages where ID=:ID");
        query.bindValue(":ID",ID);
        return query.exec();
    }

    QSqlQueryModel* Voyages::afficher(){

       QSqlQueryModel* model=new QSqlQueryModel();


             model->setQuery("SELECT* FROM VOYAGES");
             model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
             model->setHeaderData(1, Qt::Horizontal, QObject::tr("DESTINATION"));
             model->setHeaderData(2, Qt::Horizontal, QObject::tr("HOTEL"));
             model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRIX"));


       return model;

    }

    bool Voyages::Modifier(int ID,QString DESTINATION,QString HOTEL,float PRIX)
{
    QSqlQuery query;
    QString prix_string =QString::number(PRIX);
    QString id_string =QString::number(ID);
    query.prepare("UPDATE voyages SET DESTINATION=:Destination, HOTEL=:hotel, PRIX=:prix WHERE ID=:ID");
    query.bindValue(":Destination", DESTINATION);
    query.bindValue(":ID", id_string);
    query.bindValue(":hotel", HOTEL);
    query.bindValue(":prix", prix_string);

    return  query.exec();
    }



