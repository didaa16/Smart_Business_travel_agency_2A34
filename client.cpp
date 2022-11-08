#include "client.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QMessageBox>
#include<QSqlError>
#include<QObject>
Client::Client()
{
id=0; nom=""; prenom=""; numero=0;
}
Client::Client(int numtelephone,int id,QString nom,QString prenom)
{
  this->numero=numtelephone,this->id=id,this->nom=nom,this->prenom=prenom;
}

int Client::getid(){return id;}
int Client::getnumero(){return numero;}
QString Client::getnom(){return nom;}
QString Client::getprenom(){return prenom;}
void Client::setid(int id){ this->id=id;}
void Client::setnom(QString nom){this->nom=nom;}
void Client::setprenom(QString prenom){this->prenom=prenom;}
void Client::setnumero(int numero ){this->numero=numero;}
bool Client::ajouter()
{

    QSqlQuery query;
    QString id_string= QString::number(id);
          query.prepare("INSERT INTO client (ID, NOM, PRENOM,NUMERO) "
                        "VALUES (:id, :nom, :prenom,:numero)");
          query.bindValue(":id", id_string);
          query.bindValue(":nom", nom);
          query.bindValue(":prenom", prenom);
           query.bindValue(":numero", numero);
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


          model->setQuery("SELECT* FROM Client");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prenom"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("Numero"));
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



QSqlQueryModel* Client::rechercher(QString a)
{
    QSqlQueryModel * query=new QSqlQueryModel();
    query->setQuery("select * from Client where (id like '%"+a+"%'  ) ");
    return    query;
}



QSqlQueryModel *Client::trier(QString x)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    qDebug()<<x<<endl;
    if(x=="Nom")
        model->setQuery("select id,nom,prenom,numero from Client order by nom");
    else if(x=="Prénom")
        model->setQuery("select id, nom, prenom, numero from Client order by prenom");


    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("numero"));

        return model;
}
