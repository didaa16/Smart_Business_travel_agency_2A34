#include "hotel.h"
#include "mainwindow.h"
#include <QString>
#include <QMap>
#include <QSqlQuery>
#include <QtDebug>
#include <QVector>


Hotel::Hotel()
{
    id = 0 ; nom = " "; adresse = " "; num = 0; prix = 0; classe = " ";/* caracters [" "] = 0*/;
}
Hotel::Hotel(int id, QString nom , QString adresse, long num, float prix, QString classe)
{this->id = id; this->nom = nom ; this->adresse= adresse; this->num = num; this->prix = prix;
    this->classe = classe;}
int Hotel::get_id () {return  id;}
QString Hotel::get_nom(){return nom;}
QString Hotel::get_adresse (){return  adresse;}
long Hotel::get_num (){return  num;}
float Hotel::get_prix (){return prix;}
QString Hotel::get_classe (){return classe;}
QList <int> Hotel::get_reco(){return reco;}
QList <QString> Hotel::get_tabadresse () {return tabadresse;}
void Hotel::set_id (int id ){this->id = id;}
void Hotel::set_nom (QString nom){this->nom = nom ;}
void Hotel::set_adresse (QString adresse){this->adresse= adresse;}
void Hotel::set_num (long num){this->num = num;}
void Hotel::set_prix (float prix){this->prix = prix;}
void Hotel::set_classe (QString classe){this->classe = classe;}
void Hotel::set_reco(int reco ){this->reco.push_back(reco);}
bool Hotel::ajouter()
{

    QSqlQuery query;
    QString id_string = QString::number(id);
    QString num_string = QString::number(num);
    QString prix_string = QString::number(prix);
          query.prepare("INSERT INTO Hotel (id, nom, adresse, num, prix, classe) " "VALUES (:id, :nom, :adresse, :num, :prix, :classe)");
          query.bindValue(":id", id_string);
          query.bindValue(":nom", nom);
          query.bindValue(":adresse", adresse);
          query.bindValue(":num", num_string);
          query.bindValue(":prix", prix_string);
          query.bindValue(":classe", classe);
          return query.exec();

}
bool Hotel::supprimer(int id)
{
    QSqlQuery query;
    QString res = QString::number(id);
    query.prepare("Delete from Hotel where ID = :id");
    query.bindValue(":id",res);
    return  query.exec();
}
QSqlQueryModel * Hotel::afficher()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("Select * from Hotel");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Adresse"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Num"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Prix"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Classe"));
    return model;
}
bool Hotel :: modifier()
{
    QSqlQuery query;
    QString id_string = QString::number(id);
    QString num_string = QString::number(num);
    QString prix_string = QString::number(prix);
    query.prepare("UPDATE Hotel SET id= :id, nom= :nom, adresse= :adresse, num= :num, prix= :prix, classe = :classe "
                        " WHERE  ID = '"+id_string+"' ");
    query.bindValue(":id", id_string);
    query.bindValue(":nom", nom);
    query.bindValue(":adresse", adresse);
    query.bindValue(":num", num_string);
    query.bindValue(":prix", prix_string);
    query.bindValue(":classe", classe);
    return query.exec();
}
QSqlQueryModel * Hotel::afficherrecherche(QString ar)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("Select * from Hotel where id like '%"+ar+"%' or nom like '%"+ar+"%' or num like '%"+ar+"%' or adresse like '%"+ar+"%' ");
    return model;
}
QString Hotel::classification()
{
    int s=0 ,m;
    if (reco.size()== 10)
    {
        for (QList <int> ::iterator it = reco.begin(); it != reco.end();it++)
        {
            s = s+reco[*it];
        }
        m = s/10 ;
        QList <int> ::iterator i = reco.begin();
        while (i != reco.end())
        {
            i = reco.erase(i);
        }

        switch (m)
        {
        case 0:
            classe = "0 Etoile";
            break;
        case 1:
            classe = "1 Etoile";
            break;
        case 2:
            classe = "2 Etoiles";
            break;
        case 3:
            classe = "3 Etoiles";
            break;
        case 4:
            classe = "4 Etoiles";
            break;
        case 5:
            classe = "5 Etoiles";
            break;
        }
        return classe ;
    }
    else
        return classe;

}

bool Hotel::modifier_classe() //POUR CLASSIFICATION
{
    QSqlQuery query;
    QString classe = Hotel::classification();
    QString id_string = QString::number(id);
    query.prepare("UPDATE Hotel SET classe = :classe "
                        " WHERE  ID = '"+id_string+"' ");
    query.bindValue(":id", id_string);
    query.bindValue(":classe", classe);
    return query.exec();
}






