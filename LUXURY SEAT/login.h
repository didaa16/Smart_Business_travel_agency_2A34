#ifndef LOGIN_H
#define LOGIN_H

#include <QString>
#include <QSqlQueryModel>

class Login{

public:
    bool admincheck(QString);
    QString Hasher(QString);
    bool ajouter(QString,QString,int,QString,int);
    bool supp(QString);
    bool bannir(QString);
    bool bancheck(QString);
    bool mailsender();
    bool codetester(QString);
    QString emailgrabber(QString);
    int idgrabber();
    bool idchecker(QString);

};

#endif // LOGIN_H
