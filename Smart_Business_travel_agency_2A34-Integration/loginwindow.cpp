#include "loginwindow.h"
#include "ui_loginwindow.h"

#include "mainwindow.h"
#include "connection.h"
#include <QMessageBox>
#include <QString>
#include <QApplication>
#include <voyages.h>
#include "mailsender.h"
#include <QThread>



QString idforcheck;
bool islogged;

QString str;
QString email;

int i=0;

loginwindow::loginwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::loginwindow)
{
    ui->setupUi(this);

    if(islogged==false){
    ui->label_3->hide();
    ui->codebrr->hide();
    ui->codesender->hide();
    ui->label_4->hide();
    }
}

loginwindow::~loginwindow()
{
    delete ui;
}

void loginwindow::on_loginbar_clicked()
{Login E;
    Voyages E2;
    QString p;
    QString n;
        QSqlQuery query;
        n=ui->namebar->text();
        //QString b=E.Hasher(n);

        //QString status = QString("HASHED TO %1 ").arg(b);
        //QMessageBox::information(this, tr("Info"), status);

        p=E.Hasher(ui->passbar->text());






        query.prepare("SELECT* FROM LOGIN WHERE USERNAME = :name AND PASSWORD = :pass");
        query.bindValue(":name", n);
        query.bindValue(":pass", p);
        query.exec();



if(B.bancheck(n)){

    QMessageBox::critical(nullptr, QObject::tr("BANNED USER"),
                QObject::tr("your account is BANNED . please contact an admin for more informations !"), QMessageBox::Cancel);


}else{
        if(query.next()){

            str.resize(6);
            for (int s = 0; s <6 ; ++s)
                str[s] = QChar('A' + char(qrand() % ('Z' - 'A')));

            Smtp* smtp = new Smtp("MouhamedAmine.BenSalem@esprit.tn", "211JMT4113", "smtp.gmail.com", 465);
            connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
                       email=B.emailgrabber(n);

                smtp->sendMail("MouhamedAmine.BenSalem@esprit.tn",email, "CODE DE VERIFICATION","le code est le "+str);

            idforcheck=n;
            islogged=true;

            QString status = QString("Un code de verification vous a etait envoyer sur votre E-mail");
            QMessageBox::information(this, tr("Info"), status);

            ui->namebar->hide();
            ui->passbar->hide();
            ui->label->hide();
            ui->label_2->hide();
            ui->loginbar->hide();

            ui->label_3->show();
            ui->codebrr->show();
            ui->codesender->show();





        }else{
            islogged=false;
            QMessageBox::critical(nullptr, QObject::tr("OK"),
                        QObject::tr("le nom ou le mot de passe sont incorrect!"), QMessageBox::Cancel);}



}
}

void loginwindow::on_codesender_clicked()
{QString code;
    i++;
code=ui->codebrr->text();
if (i==1){
    if(code==str){
        mainwindow = new MainWindow(this);
        mainwindow->show();
    }else if(code!=str){

        QMessageBox::critical(nullptr, QObject::tr("OK"),
                                QObject::tr("le code est incorrect merci de re-essayer (DERNIERE TENTATIVE)"
                                            " un nouveau code vous sera envoyer dans quelques secondes !!"), QMessageBox::Cancel);

        str.resize(6);
        for (int s = 0; s <6 ; ++s)
            str[s] = QChar('A' + char(qrand() % ('Z' - 'A')));

        Smtp* smtp = new Smtp("MouhamedAmine.BenSalem@esprit.tn", "211JMT4113", "smtp.gmail.com", 465);
        connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


            smtp->sendMail("MouhamedAmine.BenSalem@esprit.tn",email, "CODE DE VERIFICATION","le code est le "+str);
    }

}else if(i>1){
    if(code==str){
        mainwindow = new MainWindow(this);
        mainwindow->show();
    }else if(code!=str){

        QMessageBox::critical(nullptr, QObject::tr("OK"),
                                QObject::tr("le code est incorrect Votre compte est banni contacter un ADMIN !!"), QMessageBox::Cancel);
        B.bannir(ui->namebar->text());
        Smtp* smtp = new Smtp("MouhamedAmine.BenSalem@esprit.tn", "211JMT4113", "smtp.gmail.com", 465);
        connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

            smtp->sendMail("MouhamedAmine.BenSalem@esprit.tn",email, "Signalement de faux login","acces non authorisé a votre compte detecté");
        this->close();
    }

}
}

/*void loginwindow::on_fingerpr_clicked()
{
    QByteArray bArray;

    QString str = "";

data="";

    ui->namebar->hide();
    ui->passbar->hide();
    ui->label->hide();
    ui->label_2->hide();
    ui->loginbar->hide();
    ui->label_4->show();





    if (data==""){



QThread::sleep(1);

A.write_to_arduino("2");

    QMessageBox::information(nullptr, QObject::tr("OK"),
                            QObject::tr("enter your finger when the light TURNS ON then press close !!"), QMessageBox::Close);

    while (data==""){

        data=A.read_from_arduino();
        bArray=data;
        str.append(bArray);

        qDebug() << str ;
    }
}
    if (B.idchecker(str)==true){
        if(B.bancheck(str)){
            QMessageBox::critical(nullptr, QObject::tr("BANNED USER"),
                        QObject::tr("your account is BANNED . please contact an admin for more informations !"), QMessageBox::Cancel);

        }else{
A.close_arduino();
                    //QMessageBox::information(nullptr, QObject::tr("OK"),
                                            //QObject::tr("logged in Succesfuly !!"), QMessageBox::Close);

                    Smtp* smtp = new Smtp("MouhamedAmine.BenSalem@esprit.tn", "211JMT4113", "smtp.gmail.com", 465);
                    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
                               email=B.emailgrabber(str);

                        smtp->sendMail("MouhamedAmine.BenSalem@esprit.tn",email, "Signalement de login","compte ouvert avec votre emprinte");

                        idforcheck=str;
                        islogged=true;

        mainwindow = new MainWindow(this);
        mainwindow->show();


}
    }else{

        QMessageBox::information(nullptr, QObject::tr("OK"),
                                QObject::tr("NOT A VALID FINGER PRINT!!"), QMessageBox::Close);



    }


}*/
