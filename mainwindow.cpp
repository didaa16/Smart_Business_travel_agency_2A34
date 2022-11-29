#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "facturee.h"
#include<QMessageBox>
#include<QIntValidator>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   ui->le_id->setValidator( new QIntValidator(0, 9999999, this));
   ui->le_prix->setValidator( new QIntValidator(0, 9999999, this));
   ui->nombre_du_jour->setValidator( new QIntValidator(0, 9999999, this));

   ui->tableView->setModel(M.afficher());
   ui->tabr->setModel(M1.afficher_remise());
   ui->tabs->setModel(M2.afficher_sans_remise());

   ui->tab_rem->setModel(M3.afficherremboursement());
   int ret=A.connect_arduino(); // lancer la connexion à arduino
           switch(ret){
           case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
               break;
           case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
              break;
           case(-1):qDebug() << "arduino is not available";
           }
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pd_ajouter_clicked()
{
    int id =ui->le_id->text().toInt();
    QString client =ui->le_client->text();
    int prix =ui->le_prix->text().toInt();
    int nombre_du_jour =ui->nombre_du_jour->text().toInt();
    Facturee M(id, client, prix, nombre_du_jour);

    QString test=M.ajouter();
      if (test!="erreur")
      {
          QMessageBox::information(nullptr, QObject::tr("OK"),
                                QObject::tr("Ajout effectué.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);
          ui->tableView->setModel(M.afficher());

                }
                else{
                    QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                QObject::tr("Ajout non effectué.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);

                    QByteArray x=test.toUtf8();
                    qDebug() << x ;
                    A.write_to_arduino(x);
      }

if(test=="impossible"){
    QByteArray x=test.toUtf8();
    qDebug() << x ;
    A.write_to_arduino(x);

}else {
    QByteArray x=test.toUtf8();
    qDebug() << x ;
    A.write_to_arduino(x);

}



}

void MainWindow::on_pb_supprimer_clicked()
{
    Facturee M1; M1.setid(ui->le_id_supp->text().toInt());

       bool test=M1.supprimer(M1.getid());
      QMessageBox messagebox;
       if (test)

       {
           messagebox.setText("Suppression effectué.\n"
                                         "Click Cancel to exit.");
       ui->tableView->setModel(M.afficher());

             }
             else{

                             messagebox.setText("Suppression non effectué.\n"
                                         "Click Cancel to exit.");
   }
}

void MainWindow::on_id_rechercher_textChanged(const QString &arg1)
{
    ui->tabr->setModel(M1.Rechercher_remise(arg1));
}

void MainWindow::on_id_recherche_s_textChanged(const QString &arg1)
{
   ui->tabs->setModel(M2.Rechercher_sans_remise(arg1));
}

void MainWindow::on_trier_clicked()
{
    ui->tableView->setModel(M.trier());
}


void MainWindow::on_trier_s_clicked()
{
    ui->tabs->setModel(M2.trier_sans_remise());
}


void MainWindow::on_trier_r_clicked()
{
    ui->tabr->setModel(M1.trier_remise());
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    QString pdf;
       QString val=ui->tableView->model()->data(index).toString();
       QSqlQuery qry;
       qry.prepare("SELECT * FROM FACTUREE WHERE ID=:val");
       qry.bindValue(":val",val);
       if(qry.exec())
       {
          while (qry.next()) {
              pdf=(qry.value(0).toString() + "\n" + qry.value(1).toString() + "\n" + qry.value(2).toString() + "\n" + qry.value(3).toString() + "\n" + qry.value(4).toString() + "\n");
           }
       }
       ui->pdf->setText(pdf);
}

void MainWindow::on_pb_pdf_clicked()
{
    QPrinter printer;
         printer.setPrinterName("Facture");
         QPrintDialog dialog(&printer,this);
         if (dialog.exec() == QDialog::Rejected) return;
         ui->pdf->print(&printer);
}


void MainWindow::on_pb_stat_clicked()
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
            q2.prepare("Select * from FACTUREE where MONTANTFINAL >=800 ");
            if(q2.exec())
            {
                while (q2.next())
                {
                    c1++;
                }
            }
            q3.prepare("Select * from FACTURE where MONTANTFINAL <800");
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
                    series->append("AVEC REMISE",c1);
                    series->append("SANS REMISE",c2);

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
                    ui->stat->setLayout(layout);
}


