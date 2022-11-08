#ifndef CLIENT_H
#define CLIENT_H
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QString>
#include"qsqlquery.h"
class Client
{
private:
    QString nom,prenom;
    int id;
    int numero;

public:

    Client();
    Client(int,int,QString,QString);
    QString getnom();
    QString getprenom();
    int getid();
    int getnumero();
    void setnom(QString );
    void setprenom(QString );
    void setid(int );
    void setnumero(int );
    bool ajouter();
   QSqlQueryModel* afficher();
   bool supprimer(int);
  bool Modifier(int,QString,QString,int);
   QSqlQueryModel* rechercher(QString a);
   QSqlQueryModel* trier(QString x);
};

#endif // CLIENT_H
