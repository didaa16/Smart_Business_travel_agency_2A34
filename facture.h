#ifndef FACTURE_H
#define FACTURE_H
#include<QString>
#include<QSqlQueryModel>



class Facture
{
public:
    Facture();
    Facture(int, QString,int , int, int, int remboursement);
        int getid();
        QString getclient();
        int getmontant();
        int getreduction();
        int getmontantFinal();
        int getremboursement();
        void setid(int);
        void setclient(QString);
        void setmontant(int);
        void setreduction(int);
        void setmontantFinal(int);
        void setremboursement(int);
        bool ajouter();
        QSqlQueryModel* afficher();
        bool supprimer();
        bool modifier();



private:
    int id;
    QString client;
    int montant;
    int reduction;
    int montantFinal;
    int remboursement;
};

#endif // FACTURE_H
