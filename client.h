#ifndef CLIENT_H
#define CLIENT_H

#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QString>
#include"qsqlquery.h"
class Client
{
private:
    QString nom,prenom,sexe;
    int id;
    int numero;

public:

    Client();
    Client(int,int,QString,QString,QString);
    QString getnom();
    QString getprenom();
    int getid();
    int getnumero();
    QString getsexe();
    void setnom(QString );
    void setprenom(QString );
    void setid(int );
    void setnumero(int );
    void setsexe(QString);
    bool ajouter();
   QSqlQueryModel* afficher();
   bool supprimer(int);
  bool Modifier(int,QString,QString,int);
   bool fidelite (int);
   bool modifier_prix();
   QSqlQueryModel* trier();
   QSqlQueryModel* Rechercher(QString);
QSqlQueryModel*  afficherpromo();
};

#endif // CLIENT_H
