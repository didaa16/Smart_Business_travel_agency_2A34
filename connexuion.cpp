#include "connection.h"

Connection::Connection()
{

}

bool Connection::createConnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("myproject");
db.setUserName("ghozlene");//inserer nom de l'utilisateur
db.setPassword("ghozlene");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
void Connection::closeConnection(){db.close();}
