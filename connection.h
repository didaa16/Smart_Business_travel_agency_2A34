#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class Connection
{
QSqlDatabase db;
public:
    Connection();
    bool createConnect();
    void closeConnection();
};

#endif // CONNECTION_H

