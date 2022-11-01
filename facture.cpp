#include "facture.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
Facture::Facture()
{
id=0; client=""; montant=0.0; reduction=0.0; montantFinal=0.0; remboursement=0;
}
Facture::Facture(int id, QString client, int montant, int reduction, int montantFinal, int remboursement)
{
    this->id=id;
    this->client=client;
    this->montant=montant;
    this->reduction=reduction;
    this->montantFinal=montantFinal;
    this->remboursement=remboursement;


}
int Facture::getid(){return id;}
QString Facture::getclient(){return client;}
int Facture::getmontant(){return montant;}
int Facture::getreduction(){return reduction;}
int Facture::getmontantFinal(){return montantFinal;}
int Facture::getremboursement(){return remboursement;}

void Facture::setid(int id){this->id=id;}
void Facture::setclient(QString client){this->client=client;}
void Facture::setmontant(int montant){this->montant=montant;}
void Facture::setreduction(int reduction){this->reduction=reduction;}
void Facture::setmontantFinal(int montantFinal){this->montantFinal=montantFinal;}
void Facture::setremboursement(int remboursement){this->remboursement=remboursement;}

bool Facture::ajouter()
{

    QString id_string=QString::number(id);
    QString montant_string=QString::number(montant);
    QString reduction_string=QString::number(reduction);
    QString montantFinal_string=QString::number(montantFinal);
    QString remboursement_string=QString::number(remboursement);
    QSqlQuery query;
          query.prepare("INSERT INTO facture (id, client, montant, reduction, montantFinal, remboursement) "
                        "VALUES (:id, :forename, :surname)");
          query.bindValue(0, id_string);
          query.bindValue(1, client);
          query.bindValue(2, montant_string);
          query.bindValue(3, reduction_string);
          query.bindValue(4, montantFinal_string);
          query.bindValue(5, remboursement_string);
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
QString reduction_string = QString::number(reduction);
QString monrantFinal_string = QString::number(montantFinal);
QString remboursement_string = QString::number(remboursement);


    query.prepare("UPDATE  facture SET id= :id, client= :client, montant= :montant, reduction= :reduction, montantFinal= :montantFinal, remboursement= :remboursement");
    query.addBindValue( id);
    query.addBindValue( client);
    query.addBindValue(montant);
    query.addBindValue(reduction);
    query.addBindValue(montantFinal);
    query.addBindValue(remboursement);

return
        query.exec();
}

QSqlQueryModel* Facture::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel;

        model->setQuery("SELECT* FROM facture");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifiant"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("client"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("montant"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("reduction"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("montantFinal"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("remboursement"));
 return model;
}
