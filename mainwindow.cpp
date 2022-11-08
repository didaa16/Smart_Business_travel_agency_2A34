#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"client.h"
#include"QMessageBox"
#include <QIntValidator>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     ui->le_id->setValidator( new QIntValidator(0, 9999999, this));
     ui->tab_client->setModel(c.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    int id=ui->le_id->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    int numero=ui->le_numtel->text().toInt();
    Client C(id,numero,nom,prenom);

    bool test=C.ajouter();
    if (test)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                              QObject::tr("Ajout effectué.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tab_client->setModel(c.afficher());

              }
              else{
                  QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectué.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
    }







void MainWindow::on_le_modifier_clicked()
{
    Client c2;
        int id=ui->le_idmod_2->text().toInt();
        QString prenom=ui->le_prenommod->text();
        QString nom=ui->le_nommod->text();
        float numero=ui->le_numeromod->text().toInt();
         bool test=c2.Modifier(id,nom,prenom,numero);
         if (test){
             QMessageBox::information(nullptr, QObject::tr(" OK"),
                         QObject::tr("modifier successful.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
             ui->tab_client->setModel(c.afficher());

         }
         else
         {QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                         QObject::tr("modifier failed.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);}


}

void MainWindow::on_pushButton_4_clicked()
{
    Client c1; c1.setid(ui->le_id_supp->text().toInt());

    bool test=c1.supprimer(c1.getid());
   QMessageBox messagebox;
    if (test)

    {
        messagebox.setText("Suppression effectué.\n"
                                      "Click Cancel to exit.");
    ui->tab_client->setModel(c.afficher());

          }
          else{

                          messagebox.setText("Suppression non effectué.\n"
                                      "Click Cancel to exit.");
}
}



