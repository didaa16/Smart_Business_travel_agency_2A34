#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "facture.h"
#include<QMessageBox>
#include<QIntValidator>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   ui->le_id->setValidator( new QIntValidator(0, 9999999, this));
    ui->le_montant->setValidator( new QIntValidator(0, 99999, this));
     ui->la_reduc->setValidator( new QIntValidator(0, 99999, this));
      ui->le_montantF->setValidator( new QIntValidator(0, 99999, this));
       ui->le_rem->setValidator( new QIntValidator(0, 99999, this));
       ui->tableView->setModel(F.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    int id=ui->le_id->text().toInt();
    QString client=ui->le_client->text();
    int montant=ui->le_montant->text().toInt();
    int reduction=ui->la_reduc->text().toInt();
    int montantFinal=ui->le_montantF->text().toInt();
    int remboursement=ui->le_rem->text().toInt();



    Facture F(id, client, montant, reduction, montantFinal, remboursement);

bool test=F.ajouter();
QMessageBox msgBox;
if(test)
{
    msgBox.setText("Ajout avec succes.");

    ui->tableView->setModel(F.afficher());
}
else
{
    msgBox.setText("Echec d'ajout");
            msgBox.exec();
}
}
void MainWindow::on_pb_supprimer_clicked()
{
     Facture F1;
     F1.setid(ui->le_id_supp->text().toInt());
     bool test=F1.supprimer();
     QMessageBox msgBox;
     if(test)
    { msgBox.setText("Suppression avec succes.");
     ui->tableView->setModel(F.afficher());
     }
     else {
         msgBox.setText("Echec de suppression");
                 msgBox.exec();}
}

void MainWindow::on_pushButton_4_clicked()
{

    int id=ui->id_up->text().toInt();
    QString client=ui->client_up->text();
    int montant=ui->montant_up->text().toInt();
    int reduction=ui->reduction_up->text().toInt();
    int montantFinal=ui->montantF_up->text().toInt();
    int remboursement=ui->rem_up->text().toInt();



    Facture F(id, client, montant, reduction, montantFinal, remboursement);

    bool test=F.modifier();
    QMessageBox msgBox;
    if(test)
    {
        msgBox.setText("modifier avec succes.");
        ui->tableView->setModel(F.afficher()); }
    else {
        msgBox.setText("Echec de modification");
                msgBox.exec();
    }
}
