#include "mainwindow_tba.h"
#include "ui_mainwindow_tba.h"

#include"client.h"
#include"QMessageBox"
#include <QIntValidator>
#include"arduino_tba.h"
mainwindow_tba::mainwindow_tba(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainwindow_tba)
{
    ui->setupUi(this);
    ui->le_id->setValidator( new QIntValidator(0, 9999999, this));
    ui->tab_client->setModel(c.afficher());
    ui->tab_fidelite->setModel(c3.afficherpromo());
    ui->setupUi(this);
        int ret=A.connect_arduino(); // lancer la connexion à arduino
        switch(ret){
        case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
            break;
        case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
           break;
        case(-1):qDebug() << "arduino is not available";
        }
         QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
         //le slot update_label suite à la reception du signal readyRead (reception des données).
}

mainwindow_tba::~mainwindow_tba()
{
    delete ui;
}
void mainwindow_tba::on_pushButton_clicked()
{
    int id=ui->le_id->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    int numero=ui->le_numtel->text().toInt();
    QString sexe=ui->comboBox->currentText();
    Client C(id,numero,nom,prenom,sexe);

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
    A.write_to_arduino("1");
    }







void mainwindow_tba::on_le_modifier_clicked()
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

void mainwindow_tba::on_pushButton_4_clicked()
{
    Client C1;
        C1.setnom(ui->le_id_supp->text());
        bool test=C1.supprimer(C1.getid());
        if (test){
            QMessageBox::information(nullptr, QObject::tr(" OK"),
                        QObject::tr("Delete successful.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
            ui->tab_client->setModel(C1.afficher());

        }
        else
            QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                        QObject::tr("Delete failed.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
           A.write_to_arduino("2");
}








void mainwindow_tba::on_pushButton_3_clicked()
{
    int id = ui->lineEdit_4->text().toInt();
    bool test = c.modifier_prix();
    if (test){
        QMessageBox::information(nullptr, QObject::tr(" OK"),
                    QObject::tr("modifier successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                    QObject::tr("modifier failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);}
       A.write_to_arduino("3");

}




void mainwindow_tba::on_le_pdf_clicked()
{
    QPrinter printer;

            printer.setPrinterName("Client");

            QPrintDialog dialog(&printer,this);

            if (dialog.exec() == QDialog::Rejected) return;

            ui->pdf->print(&printer);
}

void mainwindow_tba::on_le_trier_clicked()
{
    ui->tab_client->setModel(c.trier());
}

void mainwindow_tba::on_recherche_id_textChanged(const QString &arg1)
{
    ui->tab_client->setModel(c.Rechercher(arg1));
}

void mainwindow_tba::on_tab_client_clicked(const QModelIndex &index)
{
    QString pdf;
        QString val=ui->tab_client->model()->data(index).toString();
        QSqlQuery qry;
        qry.prepare("SELECT * FROM Client WHERE ID=:val");
        qry.bindValue(":val",val);
        if(qry.exec())
        {
           while (qry.next()) {
               ui->le_id->setText(qry.value(0).toString());
               ui->le_nom->setText(qry.value(1).toString());
               ui->le_prenom->setText(qry.value(2).toString());
               ui->le_numtel->setText(qry.value(3).toString());
               pdf=(qry.value(0).toString() + "\n" + qry.value(1).toString() + "\n" + qry.value(2).toString() + "\n" + qry.value(3).toString() + "\n");
          ui->pdf->setText(pdf);
           }
        }
}















void mainwindow_tba::on_le_stat_clicked()
{
    QSqlQuery q1,q2,q3,q4,q5;
            qreal tot=0,c1=0,c2=0,c3=0,c4=0;
            q1.prepare("Select * from CLIENT");
            if(q1.exec())
            {
                while (q1.next())
                {
                    tot++;
                }
            }
            q2.prepare("Select * from CLIENT where SEXE ='Homme'");
            if(q2.exec())
            {
                while (q2.next())
                {
                    c1++;
                }
            }
            q3.prepare("Select * from CLIENT where SEXE ='Femme'");
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
                        series->append("Homme",c1);
                        series->append("Femme",c2);

                        QPieSlice *slice0 = series->slices().at(0);
                        slice0->setExploded();
                        slice0->setLabelVisible();
                        slice0->setPen(QPen(Qt::darkGray, 2));
                        slice0->setBrush(Qt::gray);
                        QPieSlice *slice1 = series->slices().at(1);
                        slice1->setExploded();
                        slice1->setLabelVisible();
                        slice1->setPen(QPen(Qt::darkRed, 2));
                        slice1->setBrush(Qt::red);

                        QChart *chart = new QChart();
                        chart->addSeries(series);
                        chart->setTitle("most types");
                                    chart->setAnimationOptions(QChart::AllAnimations);
                                    chart->legend()->hide();
                                    QChartView *chartView = new QChartView(chart);
                                    chartView->setRenderHint(QPainter::Antialiasing);
                                    QGridLayout *layout = new QGridLayout();
                                    layout->addWidget(chartView);
                                    ui->stat->setLayout(layout);

}

void mainwindow_tba::on_ON_pushButton_0_clicked()
{
    A.write_to_arduino("1"); //envoyer 1 à arduino

}

void mainwindow_tba::on_ON_pushButton_1_clicked()
{
 A.write_to_arduino("0");  //envoyer 0 à arduino
}


void mainwindow_tba::on_ON_pushButton_2_clicked()
{
    A.write_to_arduino("2");   //envoyer 2 à arduino

}




void mainwindow_tba::on_ON_pushButton_3_clicked()
{
   A.write_to_arduino("3");  //envoyer 3 à arduino
}
