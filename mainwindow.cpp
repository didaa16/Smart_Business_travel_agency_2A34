#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "voyages.h"
#include "QMessageBox"
#include "QIntValidator"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->ident->setValidator(new QIntValidator(100,99999999, this));
    ui->tablevoy->setModel(E.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addbutt_clicked()
{
    int ID=ui->ident->text().toInt();
    QString DESTINATION=ui->dest->text();
    QString HOTEL=ui->hot->text();
    int PRIX=ui->prx->text().toFloat();

  Voyages E(ID,DESTINATION,HOTEL,PRIX);

  bool test=E.ajouter();
      if (test)
      {
          QMessageBox::information(nullptr, QObject::tr("OK"),
                                QObject::tr("Ajout effectué.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);

                }
                else
                    {QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                QObject::tr("Ajout non effectué.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);}

      }






void MainWindow::on_pushsupp_clicked()
{Voyages E1;
    E1.setid(ui->idsup->text().toInt());
    bool test=E1.supprimer(E1.getid());
    if (test){
        QMessageBox::information(nullptr, QObject::tr(" OK"),
                    QObject::tr("Delete successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tablevoy->setModel(E.afficher());

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                    QObject::tr("Delete failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel); }

void MainWindow::on_pushButton_2_clicked()
{

}

void MainWindow::on_pushButton_clicked()
{Voyages E2;
    int ID=ui->lineEdit->text().toInt();
    QString DESTINATION=ui->lineEdit_2->text();
    QString HOTEL=ui->lineEdit_3->text();
    float PRIX=ui->lineEdit_4->text().toFloat();
     bool test=E2.Modifier(ID,DESTINATION,HOTEL,PRIX);
     if (test){
         QMessageBox::information(nullptr, QObject::tr(" OK"),
                     QObject::tr("modifier successful.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
         ui->tablevoy->setModel(E.afficher());

     }
     else
     {QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                     QObject::tr("modifier failed.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);}
}
