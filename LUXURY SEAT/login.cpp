#include "QMessageBox"
#include <QSqlQuery>
#include <QDebug>
#include<QSqlError>
#include <QObject>
#include <string>
#include <QString>
#include <QChar>
#include "login.h"
#include "mailsender.h"


bool Login::admincheck(QString id){
bool test;
    QSqlQuery query;


    query.prepare("select* from LOGIN WHERE (USERNAME=:ID AND ADMIN='1') OR (ID=:ID AND ADMIN='1')");
    query.bindValue(":ID", id);
    query.exec();



if (query.next())
{
test=true;}
else{
    test=false;}

return test;
}


QString Login::Hasher(QString w){

QString hexx("0123456789ABCDEF");
QString hexStr,old,after;
int g=31;
int hash=0;

for (int ii(0); ii < w.length(); ii++)
{
    hexStr.append(hexx.at(w.at(ii).toLatin1() >> 4));
    hexStr.append(hexx.at(w.at(ii).toLatin1() & 0x0F));
}

for (int i=0;i<hexStr.length();i++){
hash=g*hash+(hexStr.at(i).digitValue());
}


old.setNum(hash);

for (int ii(0); ii < w.length(); ii++)
{
    after.append(hexx.at(old.at(ii).toLatin1() & 0x0F));
}


  return after;
}


bool Login::ajouter(QString user,QString pass,int ad,QString email,int id)
{

QString pass2=Hasher(pass);

QSqlQuery query;

QString ad_string=QString::number(ad);
QString id_string=QString::number(id);

           query.prepare("INSERT INTO LOGIN VALUES (:USER,:PASS,:AD,:EMA,:BAN,:ID)");
           query.bindValue(":ID", id_string);
          query.bindValue(":USER", user);
          query.bindValue(":PASS", pass2);
          query.bindValue(":AD", ad_string);
          query.bindValue(":EMA", email);
          query.bindValue(":BAN", 0);

          qDebug()<<query.lastError();
    return query.exec();


}

bool Login::supp(QString user)
{



QSqlQuery query;

          query.prepare("Delete from LOGIN where USERNAME=:USER");
          query.bindValue(":USER",user);

          qDebug()<<query.lastError();
    return query.exec();


}

bool Login::bannir(QString user)
{



QSqlQuery query;

query.prepare("UPDATE LOGIN SET BANNED='1' WHERE USERNAME=:USER");
query.bindValue(":USER", user);

          qDebug()<<query.lastError();
    return query.exec();


}


bool Login::bancheck(QString user){
bool test;
    QSqlQuery query;
    query.prepare("select* from LOGIN WHERE (USERNAME=:USER AND BANNED='1') OR (ID=:USER AND BANNED='1') ");
    query.bindValue(":USER", user);
    query.exec();

if (query.next())
{
test=true;}
else{
test=false;}

return test;
}

/*bool Login::codetester(QString code){

    QString str;
    str.resize(6);
    for (int s = 0; s <6 ; ++s)
        str[s] = QChar('A' + char(qrand() % ('Z' - 'A')));

    Smtp* smtp = new Smtp("MouhamedAmine.BenSalem@esprit.tn", "211JMT4113", "smtp.gmail.com", 465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


        smtp->sendMail("MouhamedAmine.BenSalem@esprit.tn","bensalemamine60@gmail.com", "CODE DE VERIFICATION","le code est le "+str);


}*/

QString Login::emailgrabber(QString id){
    QSqlQuery query;
    QString email;

    query.prepare("select EMAIL from LOGIN WHERE USERNAME=:USER or ID=:USER");
    query.bindValue(":USER", id);
    query.exec();

    while(query.next()){

        email=query.value("EMAIL").toString();

    }

    return email;



}

int Login::idgrabber(){
    QSqlQuery query;
    int id=0;

    query.prepare("select COUNT(*) from LOGIN");
    query.exec();

    while(query.next()){
        id=query.value("COUNT(*)").toInt();

    }
    return (id+1);
}

bool Login::idchecker(QString id){
    QSqlQuery query;
    bool test;

    query.prepare("select * from LOGIN where ID=:ID");
    query.bindValue(":ID",id);
    query.exec();
    if(query.next()){

        test=true;
    }else{
        test=false;
    }



    return test;
}
