#ifndef VOYAGES_H
#define VOYAGES_H
#include <QString>
#include <QSqlQueryModel>


class Voyages
{
public:
    Voyages();
    Voyages(int,QString,QString,float);
    int getid();
    QString getdestination();
    QString hotel();
    float getprix();
    void setid(int);
    void setdestination(QString);
    void sethotel(QString);
    void setprix(float);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool Modifier(int,QString,QString,float);




 private:
    int ID;
    QString DESTINATION,HOTEL;
    float PRIX;

};

#endif // VOYAGES_H
