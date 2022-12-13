
#ifndef FACTURE_H
#define FACTURE_H
#include<QString>
#include<QSqlQueryModel>
#include<QSqlQuery>



class Facture
{
public:
    Facture();
    Facture(int, QString, int, int remboursement , int);

     Facture(int, QString, int, int nombre_du_jour );
        int getid();
        QString getclient();
        int getprix();
        int getreduction();
        int getmontantFinal();
        int getremboursement();
        int getnombre_du_jour();
        void setid(int);
        void setclient(QString);
        void setprix(int);
        void setreduction(int);
        void setmontantFinal(int);
        void setremboursement(int);
        void setnombre_du_jour(int);
        bool ajouter();
        QSqlQueryModel* afficher();
         QSqlQueryModel* afficher_remise();
           QSqlQueryModel* afficher_sans_remise();
           QSqlQueryModel* Rechercher_remise(QString);
           QSqlQueryModel* Rechercher_sans_remise(QString);
           QSqlQueryModel* trier();
           QSqlQueryModel* trier_remise();
           QSqlQueryModel* trier_sans_remise();
          QSqlQueryModel* afficherremboursement();
        bool supprimer();
        bool modifier();
        int check();



private:
    int id;
    QString client;
    int prix;
    int nombre_du_jour;
    int remboursement;
};

#endif // FACTURE_H
