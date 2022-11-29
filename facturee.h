#ifndef FACTUREE_H
#define FACTUREE_H
#include<QString>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include"arduino.h"
class Facturee
{
public:
    Facturee();
    Facturee(int, QString, int, int);

    int getid();
    QString getclient();
    int getprix();
    int getnombre_du_jour();


    void setid(int);
    void setclient(QString);
    void setprix(int);
    void setnombre_du_jour(int);


    QString ajouter();
    bool supprimer(int);
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficher_remise();
    QSqlQueryModel* afficher_sans_remise();
    QSqlQueryModel* Rechercher_remise(QString);
    QSqlQueryModel* Rechercher_sans_remise(QString);
    QSqlQueryModel* trier();
    QSqlQueryModel* trier_remise();
    QSqlQueryModel* trier_sans_remise();
    QSqlQueryModel* afficherremboursement();



private:
    int id;
    QString client;
    int prix;
    int nombre_du_jour;
    int remboursement;
int montant_rembourse;
    QByteArray data; // variable contenant les données reçues

       Arduino A; // objet temporaire

};

#endif // FACTUREE_H
