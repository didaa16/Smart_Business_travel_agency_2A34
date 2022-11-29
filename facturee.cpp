#include "facturee.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
#include"arduino.h"
Facturee::Facturee()
{
    id=0 ; client ="" ; prix = 0 ; nombre_du_jour =0 ;
}


Facturee :: Facturee(int id, QString client, int prix, int nombre_du_jour)
{
   this->id=id;
    this->client=client;
    this->prix=prix;
    this->nombre_du_jour=nombre_du_jour;


}
int Facturee::getid() {return id;}
QString Facturee::getclient() {return client;}
int Facturee::getprix() {return prix;}
int Facturee::getnombre_du_jour() {return nombre_du_jour;}


void Facturee::setid(int id) {this->id=id;}
void Facturee::setclient(QString client) {this->client=client;}
void Facturee::setprix(int prix) {this->prix=prix;}
void Facturee::setnombre_du_jour(int nombre_du_jour) {this->nombre_du_jour=nombre_du_jour;}




QString Facturee::ajouter()
{
    int montantfinal=nombre_du_jour*prix;
    int montant_apres_remise=(montantfinal/100)*80;
    int montant_rembourse=(montant_apres_remise/100)*50;


    QString id_string= QString::number(id);
    QString prix_string= QString::number(prix);
    QString nombre_du_jour_string= QString::number(nombre_du_jour);
    QString montantfinal_string=QString::number(montantfinal);
     QString montant_apres_remise_string=QString::number(montant_apres_remise);
     QString montant_rembourse_string=QString::number(montant_rembourse);
if(montantfinal>800){return client+" "+montant_apres_remise_string; }
else {return "impossible" ;  }

    QSqlQuery query;

          query.prepare("INSERT INTO facturee (id, client, prix, nombre_du_jour, montantfinal, montant_apres_remise) "
                        "VALUES (:id, :client, :prix, :nombre_du_jour, :montantfinal, :montant_apres_remise)");
          query.bindValue(0, id_string);
          query.bindValue(1, client);
          query.bindValue(2, prix_string);
          query.bindValue(3, nombre_du_jour_string);
          query.bindValue(5,montantfinal_string);
          query.bindValue(6, montant_apres_remise_string);
          query.exec();
          return "erreur";

}

bool Facturee::supprimer(int id)
{
   QSqlQuery query;

            query.prepare(" Delete from facturee where id=:id");
            query.bindValue(0, id);
            query.exec();

     return query.exec();



}

QSqlQueryModel* Facturee::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel;

            model->setQuery("SELECT ID , CLIENT , PRIX , NOMBRE_DU_JOUR FROM FACTUREE");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifiant"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("client"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));


             model->setHeaderData(3, Qt::Horizontal, QObject::tr("nombre_du_jour"));
     return model;


}
QSqlQueryModel* Facturee::afficher_remise()
{
    QSqlQueryModel* model=new QSqlQueryModel;

        model->setQuery("SELECT ID , CLIENT , NOMBRE_DU_JOUR , MONTANTFINAL, MONTANT_APRES_REMISE FROM FACTUREE WHERE MONTANTFINAL >=800");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifiant"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("client"));


         model->setHeaderData(2, Qt::Horizontal, QObject::tr("nombre_du_jour"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("montant"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("montantfinal"));

 return model;
}


QSqlQueryModel* Facturee::afficher_sans_remise()
{
    QSqlQueryModel* model=new QSqlQueryModel;

        model->setQuery("SELECT ID , CLIENT , NOMBRE_DU_JOUR , MONTANTFINAL FROM FACTUREE WHERE MONTANTFINAL <800");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifiant"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("client"));


         model->setHeaderData(2, Qt::Horizontal, QObject::tr("nombre_du_jour"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("montantfinal"));


 return model;
}


QSqlQueryModel* Facturee::Rechercher_remise(QString d)
{
    QSqlQueryModel * model = new QSqlQueryModel();
        model->setQuery("Select ID, CLIENT, NOMBRE_DU_JOUR, MONTANTFINAL, MONTANT_APRES_REMISE from FACTUREE where id like '%"+d+"%' AND MONTANTFINAL >=800");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifiant"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("client"));


         model->setHeaderData(2, Qt::Horizontal, QObject::tr("nombre_du_jour"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("montant"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("montantfinal"));
        return model;
}


QSqlQueryModel* Facturee::Rechercher_sans_remise(QString d)
{
    QSqlQueryModel * model = new QSqlQueryModel();
        model->setQuery("Select ID, CLIENT, NOMBRE_DU_JOUR, MONTANTFINAL from FACTUREE where id like '%"+d+"%' AND MONTANTFINAL <800");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifiant"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("client"));


         model->setHeaderData(2, Qt::Horizontal, QObject::tr("nombre_du_jour"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("montantfinal"));
        return model;
}

QSqlQueryModel* Facturee::trier()
{
   QSqlQueryModel * model = new QSqlQueryModel();
   model->setQuery("SELECT id , client , prix ,nombre_du_jour FROM facturee ORDER BY nombre_du_jour ASC");

   model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifiant"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("client"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));

    model->setHeaderData(4, Qt::Horizontal, QObject::tr("nombre_du_jour"));
return model;
}




QSqlQueryModel* Facturee::trier_remise()
{QSqlQueryModel * model = new QSqlQueryModel();

   model->setQuery("SELECT ID, CLIENT, NOMBRE_DU_JOUR, MONTANTFINAL , MONTANT_APRES_REMISE from FACTUREE WHERE MONTANTFINAL >=800 ORDER BY MONTANTFINAL  ASC ");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifiant"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("client"));


    model->setHeaderData(2, Qt::Horizontal, QObject::tr("nombre_du_jour"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("montant"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("montantfinal"));
   return model;
}



 QSqlQueryModel* Facturee::trier_sans_remise()
 {QSqlQueryModel * model = new QSqlQueryModel();

     model->setQuery("SELECT ID, CLIENT, NOMBRE_DU_JOUR, MONTANTFINAL from FACTUREE WHERE MONTANTFINAL<800 ORDER BY MONTANTFINAL  ASC ");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifiant"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("client"));


      model->setHeaderData(2, Qt::Horizontal, QObject::tr("nombre_du_jour"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("montantfinal"));
     return model;
 }


 QSqlQueryModel* Facturee::afficherremboursement()
 {
     int REMBOURSEMENT=1;


     QSqlQuery query;

     QString REMBOURSEMENT_string = QString::number(REMBOURSEMENT);



         query.prepare("UPDATE  facturee SET REMBOURSEMENT= :REMBOURSEMENT WHERE( SELECT FACTUREE.ID , FACTUREE.CLIENT , FACTUREE.MONTANTFINAL , FACTUREE.REMBOURSEMENT , FACTUREE.MONTANT_REMBOURSE  FROM FACTUREE INNER JOIN  VOYAGEE ON FACTUREE.ID = VOYAGEE.ID WHERE VOYAGEE.ALERTE=1) ");
         query.addBindValue( REMBOURSEMENT);



     QSqlQueryModel* model=new QSqlQueryModel;



         model->setQuery("SELECT FACTUREE.ID , FACTUREE.CLIENT , FACTUREE.MONTANTFINAL ,   FACTUREE.REMBOURSEMENT , FACTUREE.MONTANT_REMBOURSE FROM FACTUREE INNER JOIN  VOYAGEE ON FACTUREE.ID = VOYAGEE.ID WHERE VOYAGEE.ALERTE=1 ");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifiant"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("client"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("montantfinal"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("remboursement"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("montant_rembourse"));





  return model;
 }
