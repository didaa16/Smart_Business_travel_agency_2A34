#include "client.h"

#include "client.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QMessageBox>
#include<QSqlError>
#include<QObject>
Client::Client()
{
id=0; nom=""; prenom=""; numero=0;sexe="";
}
Client::Client(int numtelephone,int id,QString nom,QString prenom,QString sexe)
{
  this->numero=numtelephone,this->id=id,this->nom=nom,this->prenom=prenom,this->sexe=sexe;
}

int Client::getid(){return id;}
int Client::getnumero(){return numero;}
QString Client::getnom(){return nom;}
QString Client::getprenom(){return prenom;}
QString Client::getsexe(){return sexe;}
void Client::setid(int id){ this->id=id;}
void Client::setnom(QString nom){this->nom=nom;}
void Client::setprenom(QString prenom){this->prenom=prenom;}
void Client::setnumero(int numero ){this->numero=numero;}
void Client::setsexe(QString sexe){this->sexe=sexe;}
bool Client::ajouter()
{
int promo=1;
    QSqlQuery query;
    QString id_string= QString::number(id);
          query.prepare("INSERT INTO client (ID, NOM, PRENOM,NUMERO,SEXE) "
                        "VALUES (:id, :nom, :prenom,:numero,:sexe)");
          query.bindValue(":id", id_string);
          query.bindValue(":nom", nom);
          query.bindValue(":prenom", prenom);
           query.bindValue(":numero", numero);
           query.bindValue(":sexe", sexe);
          qDebug()<<query.lastError();

         return query.exec();



}
bool Client::supprimer(int id)
{

    QSqlQuery query;
          query.prepare("Delete from Client where ID=:id");
          query.bindValue(":id", id);

         return query.exec();
}

QSqlQueryModel* Client::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();


          model->setQuery("SELECT ID, NOM , PRENOM , NUMERO , SEXE FROM CLIENT");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prenom"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("Numero"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("sexe"));
  return model;
}

bool Client::Modifier(int id,QString NOM,QString prenom,int numero)
{
    QSqlQuery query;
    QString numero_string =QString::number(numero);
    QString id_string =QString::number(id);
    query.prepare("UPDATE Client SET NOM=:nom, PRENOM=:PRENOM,NUMERO=:numero WHERE ID=:ID");
    query.bindValue(":PRENOM", prenom);
    query.bindValue(":ID", id_string);
    query.bindValue(":nom", NOM);
    query.bindValue(":numero", numero_string);

    return  query.exec();
    }


QSqlQueryModel* Client::trier()
{

    QSqlQueryModel * model = new QSqlQueryModel();
       model->setQuery("SELECT id , nom , prenom , numero  FROM Client ORDER BY id ASC");

       model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifiant"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("numero"));

    return model;
}





bool Client::fidelite(int id)
{
    int p =100, v =0;
    QSqlQuery qry;
    qry.prepare("SELECT * from VOYAGES,CLIENT WHERE ID =:id");
    qry.bindValue(":id", id);
    if (qry.exec())
    {
        while (qry.next())
        {
            v++;

        }
    }
    if (v >= 10)
    {
        QSqlQuery q;
        q.prepare("Select SUM (prix) from VOYAGES WHERE ID =:id");
        qry.bindValue(":id", id);
        if (q.exec())
        {
            while (q.next())
            {
                p += q.value(0).toInt();
            }
         }
        p = p * ((p*v*10)/100);

        qry.prepare("insert into CLIENT (PROMO) VALUES(:po) WHERE ID=:id " );
         qry.bindValue(":id", id);
          qry.bindValue(":po", p);
          qry.exec();

    }
    return  p;

    }

bool Client::modifier_prix()
{

    QSqlQuery query;
    QString id_string =QString::number(id);
    int prix = fidelite(id);
    query.prepare("UPDATE VOYAGE SET PRIX=:prix");
    query.bindValue(":prix", prix);
    return  query.exec();
}

QSqlQueryModel* Client::Rechercher(QString d)
{
    QSqlQueryModel * model = new QSqlQueryModel();
        model->setQuery("Select * from Client where id like '%"+d+"%' ");
        return model;
}

QSqlQueryModel* Client::afficherpromo()
 {
     int promo=1;

     QSqlQuery query;

     QString promo_string = QString::number(promo);


         query.prepare("UPDATE  Client SET promo= :promo WHERE( SELECT CLIENT.ID , CLIENT.NOM , CLIENT.PRENOM , CLIENT.NUMERO , CLIENT.PROMO  FROM CLIENT INNER JOIN  VOYAGES ON CLIENT.ID = VOYAGES.ID WHERE VOYAGES.NBRE_VOYAGE>=10) ");
         query.addBindValue( promo);



     QSqlQueryModel* model=new QSqlQueryModel;



         model->setQuery("SELECT CLIENT.ID , CLIENT.NOM , CLIENT.PRENOM ,   CLIENT.NUMERO , CLIENT.PROMO FROM CLIENT INNER JOIN  VOYAGES ON CLIENT.ID = VOYAGES.ID WHERE VOYAGES.NBRE_VOYAGE>=10 ");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifiant"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
           model->setHeaderData(4, Qt::Horizontal, QObject::tr("numero"));
           model->setHeaderData(3, Qt::Horizontal, QObject::tr("promo"));





  return model;
 }
