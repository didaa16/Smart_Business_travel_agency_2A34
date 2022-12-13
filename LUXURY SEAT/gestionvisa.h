#ifndef GESTIONVISA_H
#define GESTIONVISA_H
#include<QString>
#include<QSqlQuery>
#include<QDebug>
#include<QSqlQueryModel>
#include<QDate>

class gestionvisa
{
public:
    gestionvisa();
    gestionvisa(QString,QString,QString,QString,QString);
    QString getnum_de_passeporte();
    QString getnum_de_compte_bancaire();
    QString get_cin();
    QString getemail();
    QString getdestination();
    void setnum_de_passeporte(QString);
    void setnum_de_compte_bancaire(QString);
    void setcin(QString);
    void setemail(QString);
    void setdestination(QString);
    QSqlQueryModel * chercher(QString );
private:
  QString num_de_passeporte;
  QString num_de_compte_bancaire;
  QString cin;
  QString email;
  QString destination;
};

#endif // GESTIONVISA_H


