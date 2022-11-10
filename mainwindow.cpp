#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "hotel.h"
#include "connection.h"
#include <iostream>
#include <QMessageBox>
#include <QIntValidator>
#include <iostream>
#include <QModelIndex>
#include <QDebug>


QT_CHARTS_USE_NAMESPACE


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_11->setValidator(new QIntValidator (0,99999999,this));
    ui->lineEdit_14->setValidator(new QIntValidator);
    ui->lineEdit_311->setValidator(new QIntValidator (0,99999999,this));
    ui->lineEdit_341->setValidator(new QIntValidator);
    ui->tabaffichage->setModel(Htmp.afficher());
}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_5_clicked() //AJOUT
{
    int id = ui->lineEdit_11->text().toInt();
    QString nom = ui->lineEdit_12->text();
    QString adresse = ui->lineEdit_13->text();
    double num = ui->lineEdit_14->text().toInt();
    float prix = ui->lineEdit_15->text().toFloat();
    QString classe = ui->linecomboBox_1->currentText();
    Hotel H(id,nom,adresse,num,prix,classe);
    bool test = H.ajouter();
    if (test)
    {
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Ajout effectué \n" "Click cancel to exit."),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                                 QObject::tr("Ajout non effectué \n" "Click cancel to exit."),QMessageBox::Cancel);
    ui->lineEdit_11->clear();
    ui->lineEdit_12->clear();
    ui->lineEdit_13->clear();
    ui->lineEdit_14->clear();
    ui->lineEdit_15->clear();
    ui->linecomboBox_1->clear();
    ui->tabWidget->setCurrentIndex(1);
    ui->tabaffichage->setModel(Htmp.afficher()); //AFFICHAGE AUTO
}


void MainWindow::on_pushButton_2_clicked() //SUPPRESSION
{
    int id = ui->lineEdit_311->text().toInt();
    bool test=Htmp.supprimer(id);
    if (test)
    {
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Suppression effectué \n" "Click cancel to exit."),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                                 QObject::tr("Suppression non effectué \n" "Click cancel to exit."),QMessageBox::Cancel);
    ui->lineEdit_311->clear();
    ui->lineEdit_321->clear();
    ui->lineEdit_331->clear();
    ui->lineEdit_341->clear();
    ui->lineEdit_351->clear();
    ui->linecomboBox_2->clear();
    ui->lineEdit_361->clear();
    ui->tabaffichage->setModel(Htmp.afficher());//AFFICHAGE AUTO
}


void MainWindow::on_pushButton_clicked() //MODIFIER
{
    int id = ui->lineEdit_311->text().toInt();
    QString nom = ui->lineEdit_321->text();
    QString adresse = ui->lineEdit_331->text();
    double num = ui->lineEdit_341->text().toInt();
    float prix = ui->lineEdit_351->text().toFloat();
    QString classe = ui->linecomboBox_2->currentText();
    Hotel H(id,nom,adresse,num,prix,classe);
    bool test = H.modifier();
    if (test)
    {
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("MAJ effectué \n" "Click cancel to exit."),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                                 QObject::tr("MAJ non effectué \n" "Click cancel to exit."),QMessageBox::Cancel);
    ui->lineEdit_311->clear();
    ui->lineEdit_321->clear();
    ui->lineEdit_331->clear();
    ui->lineEdit_341->clear();
    ui->lineEdit_351->clear();
    ui->linecomboBox_2->clear();
    ui->lineEdit_361->clear();
    ui->tabaffichage->setModel(Htmp.afficher());//AFFICHAGE AUTO
}


void MainWindow::on_tabaffichage_clicked(const QModelIndex &index)//SELECT FROM TABLE VIEW
{
        QString val=ui->tabaffichage->model()->data(index).toString();
        QSqlQuery qry;
        qry.prepare("select * from Hotel where id=:val or nom=:val or adresse=:val or num=:val or prix=:val or classe=:val");
        qry.bindValue(":val",val);
        if (qry.exec())
        {
            while(qry.next())
            {
                ui->lineEdit_311->setText(qry.value(0).toString());
                ui->lineEdit_30->setText(qry.value(0).toString());
                ui->lineEdit_321->setText(qry.value(1).toString());
                ui->lineEdit_331->setText(qry.value(2).toString());
                ui->lineEdit_341->setText(qry.value(3).toString());
                ui->lineEdit_351->setText(qry.value(4).toString());
                ui->lineEdit_361->setText(qry.value(5).toString());
                QString infos = (" Id : \t" + qry.value(0).toString() + "\n Nom : \t" + qry.value(1).toString() +"\n Adresse : \t"+ qry.value(2).toString() + "\n N°Tel : \t" +qry.value(3).toString() + "\n Prix : \t"+ qry.value(4).toString() + "\n Classe : \t"+ qry.value(5).toString());
                ui->pdf->setText(infos);
            }
        }
            else
            {
               QMessageBox::warning(this,"error","no information");
            }
}


void MainWindow::on_lineEdit_342_textChanged(const QString &arg1) // RECHERCHER
{
    ui->tabaffichage->setModel(Htmp.afficherrecherche(arg1));
}

void MainWindow::on_linecomboBox_currentIndexChanged(int index) //TRIER COMBOBOX
{
    QSqlQueryModel * model = new QSqlQueryModel();
    switch (index)
    {
    case 1:
        model->setQuery("Select * from Hotel ORDER BY id ASC");
        ui->tabaffichage->setModel(model);
        break;
    case 2:
        model->setQuery("Select * from Hotel ORDER BY id DESC");
        ui->tabaffichage->setModel(model);
        break;
    case 3:
        model->setQuery("Select * from Hotel ORDER BY nom ASC");
        ui->tabaffichage->setModel(model);
        break;
    case 4:
        model->setQuery("Select * from Hotel ORDER BY nom DESC");
        ui->tabaffichage->setModel(model);
        break;
    case 5:
        model->setQuery("Select * from Hotel ORDER BY classe ASC");
        ui->tabaffichage->setModel(model);
        break;
    case 6:
        model->setQuery("Select * from Hotel ORDER BY classe DESC");
        ui->tabaffichage->setModel(model);
        break;
    case 7:
        model->setQuery("Select * from Hotel ORDER BY prix ASC");
        ui->tabaffichage->setModel(model);
        break;
    case 8:
        model->setQuery("Select * from Hotel ORDER BY prix DESC");
        ui->tabaffichage->setModel(model);
        break;
    }
}

void MainWindow::on_pushButton_8_clicked() //RECOMMENDATION & CLASSIFICATION
{
    int somme,moy;
    somme = ((ui->linecomboBox_31->currentIndex()) + (ui->linecomboBox_32->currentIndex()) + (ui->linecomboBox_33->currentIndex()) + (ui->linecomboBox_34->currentIndex()) + (ui->linecomboBox_35->currentIndex()) + (ui->linecomboBox_36->currentIndex()) + (ui->linecomboBox_37->currentIndex()) + (ui->linecomboBox_38->currentIndex()) + (ui->linecomboBox_39->currentIndex()) + (ui->linecomboBox_310->currentIndex()) + (ui->linecomboBox_311->currentIndex()));
    moy = somme/11;
    Htmp.set_reco(moy);
    QString total;
    switch (moy)
    {
    case 0:
        total = "0 Etoile";
        break;
    case 1:
        total = "1 Etoile";
        break;
    case 2:
        total = "2 Etoiles";
        break;
    case 3:
        total = "3 Etoiles";
        break;
    case 4:
        total = "4 Etoiles";
        break;
    case 5:
        total = "5 Etoiles";
        break;
    }
    ui->lineEdit->setText(total);
    int id = ui->lineEdit_30->text().toInt();
    QString nom = ui->lineEdit_321->text();
    QString adresse = ui->lineEdit_331->text();
    int num = ui->lineEdit_341->text().toInt();
    float prix = ui->lineEdit_351->text().toFloat();
    QString classe = ui->lineEdit->text();
    Hotel h(id,nom,adresse,num,prix,classe);

    bool test = h.modifier_classe();
    if (test)
    {
            QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Classification effectué \n" "Click cancel to exit."),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                                 QObject::tr("Classification non effectué \n" "Click cancel to exit."),QMessageBox::Cancel);
    ui->tabaffichage->setModel(Htmp.afficher()); //AFFICHAGE AUTO
    ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_pdf_clicked() // PDF
{
    QPrinter printer;
    printer.setPrinterName("Hotel");
    QPrintDialog dialog(&printer,this);
    if (dialog.exec() == QDialog::Rejected) return;
    ui->pdf->print(&printer);
}

void MainWindow::on_actionLuxury_Seat_triggered()//BOUTON LOGO
{
    ui->tabWidget->show();
}

void MainWindow::on_actionAjouter_triggered()//BOUTON AJOUTER
{
    ui->tabWidget->show();
    ui->tabWidget->setCurrentIndex(0);
}

void MainWindow::on_actionAfficher_triggered() //BOUTON AFFICHER
{
    ui->tabWidget->show();
    ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::on_actionRecommender_triggered() //BOUTON RECOMMENDATION
{
    ui->tabWidget->show();
    ui->tabWidget->setCurrentIndex(2);
}

void MainWindow::on_actionPdf_triggered() //BOUTON PDF
{
    ui->tabWidget->show();
    ui->tabWidget->setCurrentIndex(3);
}

void MainWindow::on_actionStatiqtiques_triggered() //STATISTIQUES
{
    ui->tabWidget->show();
    ui->tabWidget->setCurrentIndex(4);
    QSqlQuery q1,q2,q3,q4,q5,q6;
    qreal tot=0,c1=0,c2=0,c3=0,c4=0,c5=0;
    q1.prepare("Select * from Hotel");
    if(q1.exec())
    {
        while (q1.next())
        {
            tot++;
        }
    }
    q2.prepare("Select * from Hotel where classe ='1 Etoile'");
    if(q2.exec())
    {
        while (q2.next())
        {
            c1++;
        }
    }
    q3.prepare("Select * from Hotel where classe ='2 Etoiles'");
    if(q3.exec())
    {
        while (q3.next())
        {
            c2++;
        }
    }
    q4.prepare("Select * from Hotel where classe ='3 Etoiles'");
    if(q4.exec())
    {
        while (q4.next())
        {
            c3++;
        }
    }
    q5.prepare("Select * from Hotel where classe ='4 Etoiles'");
    if(q5.exec())
    {
        while (q5.next())
        {
            c4++;
        }
    }
    q6.prepare("Select * from Hotel where classe ='5 Etoiles'");
    if(q6.exec())
    {
        while (q6.next())
        {
            c5++;
        }
    }
    c1=c1/tot;
    c2=c2/tot;
    c3=c3/tot;
    c4=c4/tot;
    c5=c5/tot;
    QPieSeries *series = new QPieSeries();
            series->append("1 Etoiles",c1);
            series->append("2 Etoiles",c2);
            series->append("3 Etoiles",c3);
            series->append("4 Etoiles",c4);
            series->append("5 Etoiles",c5);
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
            QPieSlice *slice2 = series->slices().at(2);
            slice2->setExploded();
            slice2->setLabelVisible();
            slice2->setPen(QPen(Qt::darkYellow, 2));
            slice2->setBrush(Qt::yellow);
            QPieSlice *slice3 = series->slices().at(3);
            slice3->setExploded();
            slice3->setLabelVisible();
            slice3->setPen(QPen(Qt::darkGreen, 2));
            slice3->setBrush(Qt::green);
            QPieSlice *slice4 = series->slices().at(4);
            slice4->setExploded();
            slice4->setLabelVisible();
            slice4->setPen(QPen(Qt::blue, 2));
            slice4->setBrush(Qt::cyan);
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

void MainWindow::on_tabWidget_tabCloseRequested(int index) //CLOSE TAB
{
    ui->tabWidget->removeTab(index);
}

void MainWindow::on_actionQuitter_triggered()// QUITTER
{
    ui->tabWidget->close();
}




void MainWindow::on_pushButton_4_clicked() //RETOUR D'AFFICHER
{
    ui->tabWidget->close();
}

void MainWindow::on_pushButton_11_clicked() //RETOUR DE RECOMMENDATION
{
    ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_10_clicked() //RETOUR DE PDF
{
    ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_7_clicked() //RETOUR DE STATS
{
    ui->tabWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_6_clicked() //ANNULER D'AJOUT
{
    ui->tabWidget->close();
}


