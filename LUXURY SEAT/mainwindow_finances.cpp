#include "mainwindow_finances.h"
#include "ui_mainwindow_finances.h"
#include "facture.h"
#include<QMessageBox>
#include<QIntValidator>
mainwindow_finances::mainwindow_finances(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainwindow_finances)
{
    ui->setupUi(this);
    ui->le_id->setValidator( new QIntValidator(0, 9999999, this));
    ui->le_montant->setValidator( new QIntValidator(0, 99999, this));
    ui->tableView->setModel(F.afficher());
    ui->tabr->setModel(F1.afficher_remise());
    ui->tabs->setModel(F2.afficher_sans_remise());

    ui->tab_rem_1->setModel(F3.afficherremboursement());
}

mainwindow_finances::~mainwindow_finances()
{
    delete ui;
}
void mainwindow_finances::on_pushButton_clicked()
{
    int id =ui->le_id->text().toInt();
    QString client =ui->le_client->text();
    int prix =ui->le_montant->text().toInt();
    int nombre_du_jour =ui->nombre_du_jour->text().toInt();
    Facture F(id, client, prix, nombre_du_jour);
    int montantfinal=nombre_du_jour*prix;
    int montant_apres_remise=(montantfinal/100)*80;
    QString montant_apres_remise_string=QString::number(montant_apres_remise);
    QString test1 ;
    if(montantfinal>800)
    {
        test1 = client+"  "+montant_apres_remise_string;
    }
    else
    {
        test1 = "impossible" ;
    }
    bool test=F.ajouter();
      if (test)
      {
          QMessageBox::information(nullptr, QObject::tr("OK"),
                                QObject::tr("Ajout effectué.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);

      }
      else
      {
                    QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                QObject::tr("Ajout non effectué.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);
      }
      ui->tableView->setModel(F.afficher());
      ui->tabr->setModel(F1.afficher_remise());
      ui->tabs->setModel(F2.afficher_sans_remise());


if(test1=="impossible")
{
    QByteArray x=test1.toUtf8();
    qDebug() << x ;
    AF.write_to_arduino(x);

}
else
{
    QByteArray x=test1.toUtf8();
    qDebug() << x ;
    AF.write_to_arduino(x);
}



}

void mainwindow_finances::on_pb_supprimer_clicked()
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

void mainwindow_finances::on_pushButton_4_clicked()
{

    int id=ui->id_up->text().toInt();
    QString client=ui->client_up->text();
    int montant=ui->montant_up->text().toInt();
    int nombre_du_jour=ui->nombre_du_jour_up->text().toInt();
    Facture F(id, client, montant, nombre_du_jour);

    bool test=F.modifier();
    if(test)
    {
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("UPDATE effectué \n" "Click cancel to exit."),QMessageBox::Cancel);
         }
    else {
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                                 QObject::tr("UPDATE non effectué \n" "Click cancel to exit."),QMessageBox::Cancel);
    }
    ui->tableView->setModel(F.afficher());
}


void mainwindow_finances::on_id_rechercher_textChanged(const QString &arg1)
{
    ui->tabr->setModel(F1.Rechercher_remise(arg1));
}

void mainwindow_finances::on_id_rech_textChanged(const QString &arg1)
{
    ui->tabs->setModel(F2.Rechercher_sans_remise(arg1));
}


void mainwindow_finances::on_tri_clicked()
{
    ui->tableView->setModel(F.trier());
}

void mainwindow_finances::on_trier_rem_clicked()
{
    ui->tabr->setModel(F1.trier_remise());
}

void mainwindow_finances::on_trier_sans_clicked()
{
    ui->tabs->setModel(F2.trier_sans_remise());
}

void mainwindow_finances::on_tableView_clicked(const QModelIndex &index)
{
    QString pdf;
    QString val=ui->tableView->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("SELECT * FROM FACTURE WHERE ID=:val");
    qry.bindValue(":val",val);
    if(qry.exec())
    {
       while (qry.next()) {
           pdf=(qry.value(0).toString() + "\n" + qry.value(1).toString() + "\n" + qry.value(2).toString() + "\n" + qry.value(3).toString() + "\n" + qry.value(4).toString() + "\n");
        }
    }
    ui->pdf1->setText(pdf);
}

void mainwindow_finances::on_pdf_clicked()
{
   QPrinter printer;
        printer.setPrinterName("Facture");
        QPrintDialog dialog(&printer,this);
        if (dialog.exec() == QDialog::Rejected) return;
        ui->pdf1->print(&printer);
}








void mainwindow_finances::on_stat_clicked()
{
    QSqlQuery q1,q2,q3;
        qreal tot=0,c1=0,c2=0;
        q1.prepare("Select * from FACTURE");
        if(q1.exec())
        {
            while (q1.next())
            {
                tot++;
            }
        }
        q2.prepare("Select * from FACTURE where MONTANT_REMBOURSE = 0 ");
        if(q2.exec())
        {
            while (q2.next())
            {
                c1++;
            }
        }
        q3.prepare("Select * from FACTURE where MONTANT_REMBOURSE > 0");
        if(q3.exec())
        {
            while (q3.next())
            {
                c2++;
            }
        }

        c1=c1/tot;
        c2=c2/tot;
        QPieSeries *series = new QPieSeries();
                series->append("SANS REMBOURSEMENT",c1);
                series->append("REMBOURSEMENT",c2);

                QPieSlice *slice0 = series->slices().at(0);
                slice0->setExploded();
                slice0->setLabelVisible();
                slice0->setPen(QPen(Qt::darkBlue, 2));
                slice0->setBrush(Qt::blue);
                QPieSlice *slice1 = series->slices().at(1);
                slice1->setExploded();
                slice1->setLabelVisible();
                slice1->setPen(QPen(Qt::darkYellow, 2));
                slice1->setBrush(Qt::yellow);
                QChart *chart = new QChart();
                chart->addSeries(series);
                chart->setTitle("MOST CLASSES SAVED");
                chart->setAnimationOptions(QChart::AllAnimations);
                chart->legend()->hide();
                QChartView *chartView = new QChartView(chart);
                chartView->setRenderHint(QPainter::Antialiasing);
                QGridLayout *layout = new QGridLayout();
                layout->addWidget(chartView);
                ui->statistiques->setLayout(layout);
}
