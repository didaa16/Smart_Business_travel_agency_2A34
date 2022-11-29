#include "facture.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
Facture::Facture()
{
id=0; client=""; montant=0.0;  remboursement=0; nombre_du_jour=0;
}
Facture::Facture(int id, QString client, int montant,  int remboursement , int nombre_du_jour)
{
    this->id=id;
    this->client=client;
    this->montant=montant;
    this->remboursement=remboursement;
    this->nombre_du_jour=nombre_du_jour;


}

Facture::Facture(int id, QString client, int montant,  int nombre_du_jour )
{
    this->id=id;
    this->client=client;
    this->montant=montant;
    this->nombre_du_jour=nombre_du_jour;



}
int Facture::getid(){return id;}
QString Facture::getclient(){return client;}
int Facture::getmontant(){return montant;}

int Facture::getremboursement(){return remboursement;}
int Facture::getnombre_du_jour(){return nombre_du_jour;}

void Facture::setid(int id){this->id=id;}
void Facture::setclient(QString client){this->client=client;}
void Facture::setmontant(int montant){this->montant=montant;}

void Facture::setremboursement(int remboursement){this->remboursement=remboursement;}
void Facture::setnombre_du_jour(int nombre_du_jour){this->nombre_du_jour=nombre_du_jour;}

bool Facture::ajouter()
{
int montantfinal=nombre_du_jour*montant;
int montant_apres_remise=(montantfinal/100)*80;
int montant_rembourse=(montantfinal/100)*50;

    QString id_string=QString::number(id);
    QString montant_string=QString::number(montant);
     QString nombre_du_jour_string=QString::number(nombre_du_jour);


    QSqlQuery query;
          query.prepare("INSERT INTO FACTURE (ID, CLIENT , MONTANT , NOMBRE_DU_JOUR ) "
                        "VALUES (:ID, :CLIENT, :MONTANT , :NOMBRE_DU_JOUR )");
          query.bindValue(0, id_string);
          query.bindValue(1, client);
          query.bindValue(2, montant_string);

          query.bindValue(3, nombre_du_jour_string);


          query.exec();


}
bool Facture::supprimer()
{
    QSqlQuery query;
          query.prepare(" Delete from facture where id=:id");
          query.bindValue(0, id);
          query.exec();




}
bool Facture::modifier()
{

QSqlQuery query;
QString id_string = QString::number(id);
QString montant_string = QString::number(montant);

QString remboursement_string = QString::number(remboursement);


    query.prepare("UPDATE  facture SET id= :id, client= :client, montant= :montant, reduction= :reduction, montantFinal= :montantFinal");
    query.addBindValue( id);
    query.addBindValue( client);
    query.addBindValue(montant);

return
        query.exec();
}

QSqlQueryModel* Facture::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel;

        model->setQuery("SELECT ID , CLIENT , MONTANT  , NOMBRE_DU_JOUR FROM FACTURE");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifiant"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("client"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("montant"));


         model->setHeaderData(3, Qt::Horizontal, QObject::tr("nombre_du_jour"));
 return model;
}
QSqlQueryModel* Facture::afficher_remise()
{
    QSqlQueryModel* model=new QSqlQueryModel;

        model->setQuery("SELECT ID , CLIENT ,NOMBRE_DU_JOUR , MONTANTFINAL, MONTANT_APRES_REMISE FROM FACTURE WHERE MONTANTFINAL >=800");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifiant"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("client"));


         model->setHeaderData(2, Qt::Horizontal, QObject::tr("nombre_du_jour"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("montant"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("montantfinal"));

 return model;
}
QSqlQueryModel* Facture::afficher_sans_remise()
{
    QSqlQueryModel* model=new QSqlQueryModel;

        model->setQuery("SELECT ID , CLIENT ,NOMBRE_DU_JOUR , MONTANTFINAL FROM FACTURE WHERE MONTANTFINAL <800");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifiant"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("client"));


         model->setHeaderData(2, Qt::Horizontal, QObject::tr("nombre_du_jour"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("montantfinal"));


 return model;
}


QSqlQueryModel* Facture::afficherremboursement()
{
    int REMBOURSEMENT=1;

    QSqlQuery query;

    QString REMBOURSEMENT_string = QString::number(REMBOURSEMENT);


        query.prepare("UPDATE  FACTURE SET REMBOURSEMENT= :REMBOURSEMENT WHERE( SELECT FACTURE.ID , FACTURE.CLIENT , FACTURE.MONTANTFINAL , FACTURE.MONTANT_REMBOURSE , FACTURE.REMBOURSEMENT  FROM FACTURE INNER JOIN  VOYAGE ON FACTURE.ID = VOYAGE.ID WHERE VOYAGE.ALERTE=1) ");
        query.addBindValue( remboursement);



    QSqlQueryModel* model=new QSqlQueryModel;



        model->setQuery("SELECT FACTURE.ID , FACTURE.CLIENT , FACTURE.MONTANTFINAL , FACTURE.MONTANT_REMBOURSE , FACTURE.REMBOURSEMENT  FROM FACTURE INNER JOIN  VOYAGE ON FACTURE.ID = VOYAGE.ID WHERE VOYAGE.ALERTE=1 ");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifiant"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("client"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("montantfinal"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("montant_rembourse"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("remboursement"));




 return model;
}
