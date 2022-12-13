#include "facture.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
Facture::Facture()
{
id=0; client=""; prix=0.0;  remboursement=0; nombre_du_jour=0;
}
Facture::Facture(int id, QString client, int prix,  int remboursement , int nombre_du_jour)
{
    this->id=id;
    this->client=client;
    this->prix=prix;
    this->remboursement=remboursement;
    this->nombre_du_jour=nombre_du_jour;


}


Facture::Facture(int id, QString client, int prix,  int nombre_du_jour )
{
    this->id=id;
    this->client=client;
    this->prix=prix;
    this->nombre_du_jour=nombre_du_jour;
}
int Facture::getid(){return id;}
QString Facture::getclient(){return client;}
int Facture::getprix(){return prix;}

int Facture::getnombre_du_jour(){return nombre_du_jour;}

void Facture::setid(int id){this->id=id;}
void Facture::setclient(QString client){this->client=client;}
void Facture::setprix(int montant){this->prix=montant;}


void Facture::setnombre_du_jour(int nombre_du_jour){this->nombre_du_jour=nombre_du_jour;}

bool Facture::ajouter()
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


    QSqlQuery query;

    query.prepare("INSERT INTO FACTURE(ID , CLIENT , PRIX , NOMBRE_DU_JOUR ,MONTANTFINAL , MONTANT_APRES_REMISE, MONTANT_REMBOURSE) "
    "VALUES (:id, :client, :prix, :nombre_du_jour , :montantfinal , :montant_apres_remise , :montant_rembourse)");
    query.bindValue(":id", id_string);
    query.bindValue(":client", client);
    query.bindValue(":prix", prix_string);
    query.bindValue(":nombre_du_jour", nombre_du_jour_string);

    query.bindValue(":montantfinal",montantfinal_string);
    query.bindValue(":montant_apres_remise", montant_apres_remise_string);
    query.bindValue(":montant_rembourse", montant_rembourse_string);

    return query.exec();

}
/*bool Facture::ajouter()
{
    int montantfinal=nombre_du_jour*prix;
    int montant_apres_remise=(montantfinal/100)*80;
    int montant_rembourse=(montant_apres_remise/100)*50;
    QString id_string=QString::number(id);
    QString prix_string=QString::number(prix);
    QString nombre_du_jour_string=QString::number(nombre_du_jour);

    QString montantfinal_string=QString::number(montantfinal);
    QString montant_apres_remise_string=QString::number(montant_apres_remise);
     QString  montant_rembourse_string=QString::number( montant_rembourse);

    QSqlQuery query;
    query.prepare("INSERT INTO FACTURE(ID , CLIENT , PRIX , NOMBRE_DU_JOUR ,MONTANTFINAL , MONTANT_APRES_REMISE, MONTANT_REMBOURSE) "
    "VALUES (:id, :client, :prix, :nombre_du_jour , :montantfinal , :montant_apres_remise , :montant_rembourse)");
    query.bindValue(":id", id_string);
    query.bindValue(":client", client);
    query.bindValue(":prix", prix_string);
    query.bindValue(":nombre_du_jour", nombre_du_jour_string);

    query.bindValue(":montantfinal",montantfinal_string);
    query.bindValue(":montant_apres_remise", montant_apres_remise_string);
    query.bindValue(":montant_rembourse", montant_rembourse_string);
    return  query.exec();

}
 int Facture ::check()
 {
     QSqlQuery query;
     int montant_final ;
     QString id_string = QString::number(id);
     query.prepare("SELECT MONTANTFINAL FROM FACTURE WHERE  ID = '"+id_string+"' ");
     query.bindValue(":id", id_string);
     montant_final = query.value(3).toInt();
     return  montant_final ;
 }*/


bool Facture::supprimer()
{
    QSqlQuery query;
          query.prepare(" Delete from FACTURE where id=:id");
          query.bindValue(0, id);
          return query.exec();




}
bool Facture::modifier()
{

QSqlQuery query;
QString id_string = QString::number(id);
QString prix_string = QString::number(prix);
QString nombre_du_jour_string=QString::number(nombre_du_jour);


    query.prepare("UPDATE  facture SET id= :id, client= :client, prix= :prix, nombre_du_jour= :nombre_du_jour");
    query.bindValue(":id" ,id_string);
    query.bindValue(":client" ,client);
    query.bindValue(":prix" , prix_string);
    query.bindValue(":nombre_du_jour" ,nombre_du_jour_string);


    return query.exec();
}

QSqlQueryModel* Facture::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel;

        model->setQuery("SELECT id , client , prix ,nombre_du_jour FROM facture");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifiant"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("client"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));


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
QSqlQueryModel* Facture::Rechercher_remise(QString d)
{
    QSqlQueryModel * model = new QSqlQueryModel();
        model->setQuery("Select * from FACTURE where id like '%"+d+"%' AND MONTANTFINAL >=800");
        return model;
}
QSqlQueryModel* Facture::Rechercher_sans_remise(QString d)
{
    QSqlQueryModel * model = new QSqlQueryModel();
        model->setQuery("Select * from FACTURE where id like '%"+d+"%' AND MONTANTFINAL <800");
        return model;
}

QSqlQueryModel* Facture::trier()
{
   QSqlQueryModel * model = new QSqlQueryModel();
   model->setQuery("SELECT id , client , prix ,nombre_du_jour FROM facture ORDER BY nombre_du_jour ASC");

   model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifiant"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("client"));

   model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));

    model->setHeaderData(3, Qt::Horizontal, QObject::tr("nombre_du_jour"));
return model;
}




QSqlQueryModel* Facture::trier_remise()
{QSqlQueryModel * model = new QSqlQueryModel();

   model->setQuery("SELECT ID, CLIENT, NOMBRE_DU_JOUR, MONTANTFINAL , MONTANT_APRES_REMISE from FACTURE WHERE MONTANTFINAL >=800 ORDER BY MONTANTFINAL  ASC ");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifiant"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("client"));


    model->setHeaderData(2, Qt::Horizontal, QObject::tr("nombre_du_jour"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("montant"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("montantfinal"));
   return model;
}



 QSqlQueryModel* Facture::trier_sans_remise()
 {QSqlQueryModel * model = new QSqlQueryModel();

     model->setQuery("SELECT ID, CLIENT, NOMBRE_DU_JOUR, MONTANTFINAL from FACTURE WHERE MONTANTFINAL<800 ORDER BY MONTANTFINAL  ASC ");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifiant"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("client"));


      model->setHeaderData(2, Qt::Horizontal, QObject::tr("nombre_du_jour"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("montantfinal"));
     return model;
 }

 QSqlQueryModel* Facture::afficherremboursement()
 {


     QSqlQuery query;





     QSqlQueryModel* model=new QSqlQueryModel;



         model->setQuery("SELECT FACTURE.ID , FACTURE.CLIENT , FACTURE.MONTANTFINAL , FACTURE.MONTANT_REMBOURSE FROM FACTURE INNER JOIN  VOYAGEE ON FACTURE.ID = VOYAGEE.ID WHERE VOYAGEE.ALERTE=1 ");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifiant"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("client"));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr("montantfinal"));

           model->setHeaderData(3, Qt::Horizontal, QObject::tr("montant_rembourse"));





  return model;
 }

