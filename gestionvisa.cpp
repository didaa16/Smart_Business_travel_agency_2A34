#include "gestionvisa.h"
#include<QSqlDatabase>
#include<QObject>
gestionvisa::gestionvisa()
{
num_de_passeporte=" ";
num_de_compte_bancaire=" ";
cin="";
email="";
destination="";
}
gestionvisa::gestionvisa (QString num_de_passeporte,QString num_de_compte_bancaire,QString cin,QString email,QString destination)
{
    this->num_de_passeporte=num_de_passeporte;
    this->num_de_compte_bancaire=num_de_compte_bancaire;
    this->cin=cin;
    this->email=email;
    this->destination=destination;


}
QString gestionvisa::getnum_de_passeporte()
{
    return num_de_passeporte;
}
QString gestionvisa:: getnum_de_compte_bancaire()
{
    return num_de_compte_bancaire;
}
QString gestionvisa::get_cin()
{
    return cin;
}
QString gestionvisa::getemail()
{
    return email;
}
QString gestionvisa::getdestination()
{
    return destination;
}

void gestionvisa:: setnum_de_passeporte(QString num_de_passeporte)
{
    this->num_de_passeporte=num_de_passeporte;
}
void gestionvisa::setnum_de_compte_bancaire(QString num_de_compte_bancaire)
{
    this->num_de_compte_bancaire=num_de_compte_bancaire;
}
void gestionvisa::setcin(QString cin)
{
    this->cin=cin;

}
void gestionvisa::setemail(QString email)
{
    this->email=email;
}
QSqlQueryModel * gestionvisa::chercher(QString ar)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("Select * from VISA where CIN like '%"+ar+"%'");
    return model;
}

