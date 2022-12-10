#include "mainwindow_voy.h"
#include "ui_mainwindow_voya.h"
#include "voyages.h"
#include "QMessageBox"
#include "QIntValidator"
#include "QPrinter"
#include "QPrintDialog"
#include "QTextStream"
#include <QSqlQuery>
#include "QTextDocument"
#include "QPainter"
#include <QApplication>
//#include <login.h>
#include <QThread>
#include <QDebug>
#include <QObject>


//include statistique
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

extern QString idforcheck;
extern bool islogged;

MainWindow_voy::MainWindow_voy(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow_voy)
{bool test;



    ui->setupUi(this);
    ui->ident->setValidator(new QIntValidator(1,99999999, this));
    ui->prx->setValidator(new QIntValidator(100,99999999, this));
    ui->idsup->setValidator(new QIntValidator(1,99999999, this));
     ui->lineEdit->setValidator(new QIntValidator(1,99999999, this));
     ui->lineEdit_4->setValidator(new QIntValidator(1,99999999, this));


    if (islogged==true){

        test=B.admincheck(idforcheck);

        if(test==true){
     ui->Admin->setEnabled(true);
     QMessageBox::information(nullptr, QObject::tr(" OK"),
                 QObject::tr("Login Succesful.\n"
                             "You are logged as (ADMIN) Click Cancel to exit."), QMessageBox::Cancel);
}else{
        QMessageBox::information(nullptr, QObject::tr(" OK"),
                    QObject::tr("Login Succesful.\n"
                                "You are logged as (USER) Click Cancel to exit."), QMessageBox::Cancel);
    }}

    ui->tablevoy->setModel(E.afficher(0));


    int test2=A.connect_arduino();

    if(test2==0){
        qDebug()<<"MEGA connected succesfully to port "<<A.getArduinoPortname();
    }else if (test2==1){
        qDebug()<<" MEGA card found but not connected "<<A.getArduinoPortname();
    }else if (test2==-1){
        qDebug()<<"MEGA arduino card not found ";
    }

    int test3=A1.connect_arduino1();

    if(test3==0){
        qDebug()<<"UNO connected succesfully to port "<<A1.getArduinoPortname1();
    }else if (test3==1){
        qDebug()<<"UNO card found but not connected "<<A1.getArduinoPortname1();
    }else if (test3==-1){
        qDebug()<<"UNO arduino card not found ";
    }

    QObject::connect(A1.getserial1(),SIGNAL(readyRead()),this,SLOT(update_label()));




}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_label()
{
    data1=A1.read_from_arduino1();

    if(data1=="5"){
        QSqlDatabase db;
                       QTableView tablevoy;
                       QSqlQueryModel * Modal=new  QSqlQueryModel();

                       QSqlQuery query;
                        query.prepare("SELECT* FROM VOYAGES ");
                        query.exec();
                        Modal->setQuery(query);
                       tablevoy.setModel(Modal);



                        db.close();


                        QString strStream;
                        QTextStream out(&strStream);

                        const int rowCount = tablevoy.model()->rowCount();
                        const int columnCount =  tablevoy.model()->columnCount();


                        const QString strTitle ="Document";


                        out <<  "<html>\n"
                            "<head>\n"
                                "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                            <<  QString("<title>%1</title>\n").arg(strTitle)
                            <<  "</head>\n"
                            "<body bgcolor=#ffffff link=#5000A0>\n"
                           << QString("<h3 style=\" font-size: 100px; font-family: Arial, Helvetica, sans-serif; color:#ff0500; font-weight: lighter; text-align: center;\">%1</h3>\n").arg("Liste des Voyages Disponibles")
                           <<"<br>"

                            <<"<table border=2 cellspacing=1 cellpadding=10>\n";

                        out << "<thead><tr bgcolor=#f0f0f0>";
                        for (int column = 0; column < columnCount; column++)
                            if (!tablevoy.isColumnHidden(column))
                                out << QString("<th>%1</th>").arg(tablevoy.model()->headerData(column, Qt::Horizontal).toString());
                        out << "</tr></thead>\n";

                        for (int row = 0; row < rowCount; row++) {
                            out << "<tr>";
                            for (int column = 0; column < columnCount; column++) {
                                if (!tablevoy.isColumnHidden(column)) {
                                    QString data = tablevoy.model()->data(tablevoy.model()->index(row, column)).toString().simplified();
                                    out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                }
                            }
                            out << "</tr>\n";
                        }
                        out <<  "</table>\n"
                                "<br><br>"
                                //<< QString("<p><img src=":/img/aze.png"; width="200"; height="200";\">%1</p>\n")
                                <<"<br>"
                                <<"<table border=1 cellspacing=0 cellpadding=2>\n";


                            out << "<thead><tr bgcolor=#f0f0f0>";

                                out <<  "</table>\n"

                            "</body>\n"
                            "</html>\n";

                        QTextDocument *document = new QTextDocument();
                        document->setHtml(strStream);

                        QPrinter printer;
                        QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                        if (dialog->exec() == QDialog::Accepted) {

                            QLabel lab;
                             QPixmap pixmap(":/img/aze.png");
                            lab.setPixmap(pixmap);
                            QPainter painter(&lab);

                          //  QPrinter printer(QPrinter::PrinterResolution);

                          //  pixmap.load("aze.png");
                           // painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
                            //painter.drawPixmap(10,10,50,50, pixmap);
                            document->print(&printer);
                        }

                        printer.setOutputFormat(QPrinter::PdfFormat);
                        printer.setPaperSize(QPrinter::A4);
                        printer.setOutputFileName("/tmp/commandes.pdf");
                        printer.setPageMargins(QMarginsF(15, 15, 15, 15));



                        delete document;
    }else if (data1=="6"){
        QT_CHARTS_USE_NAMESPACE
                 MainWindow w;

                // Assign names to the set of bars used
                 QSqlQuery query;

        query.prepare("SELECT  count (ID) FROM VOYAGES ");
        query.exec();
            int a;
                while(query.next())
                {

                      a = query.value(0).toInt();//Récupère le résultat de la requête


                }

        QBarSet *set0 = new QBarSet("Voyage ajouter");

       *set0 << 2 << 3 << 5 << 3 << 4 << a ;

        QBarSeries *series = new QBarSeries();
        series->append(set0);

        QChart *chart = new QChart();

        // Add the chart
        chart->addSeries(series);
        chart->setAnimationOptions(QChart::AllAnimations);

        // Holds the category titles
        QStringList categories;

        categories<< "Janvier" << "Février" << "Mars"  << "Mai" << "Juin" << "Juillet" ;

        // Adds categories to the axes
        QBarCategoryAxis *axis = new QBarCategoryAxis();
        axis->append(categories);
        chart->createDefaultAxes();
        chart->setAxisX(axis, series);

        chart->legend()->setAlignment(Qt::AlignBottom);



        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        // Used to change the palette
        QPalette pal = qApp->palette();

        // Change the color around the chart widget and text
        pal.setColor(QPalette::Window, QRgb(0xff9999));
        pal.setColor(QPalette::WindowText, QRgb(0x660000));

        // Apply palette changes to the application
        qApp->setPalette(pal);

        // Customize the title font
            QFont font;
            font.setPixelSize(40);
            chart->setTitleFont(font);
            chart->setTitleBrush(QBrush(Qt::cyan));
            chart->setTitle("statistique Voyages");

        QMainWindow window;


    setCentralWidget(chartView);

    }

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
          ui->tablevoy->setModel(E.afficher(0));
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
        ui->tablevoy->setModel(E.afficher(0));

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
         ui->tablevoy->setModel(E.afficher(0));

     }
     else
     {QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                     QObject::tr("modifier failed.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);}
}

void MainWindow::on_rechbtt_clicked()
{ Voyages E3;



if (ui->identrech->text().length()>0){
    QString id=ui->identrech->text();
ui->Rechtab->setModel(E3.afficherrech(id,1));
}
else if (ui->identrech_2->text().length()>0){
    QString id=ui->identrech_2->text();
    ui->Rechtab->setModel(E3.afficherrech(id,2));

}
else{
    QMessageBox::information(nullptr, QObject::tr(" OK"),
                QObject::tr("les champs sont vide merci d'en remplire un"), QMessageBox::Cancel);

}



}










void MainWindow::on_EXPORTING_clicked()
{


        QSqlDatabase db;
                       QTableView tablevoy;
                       QSqlQueryModel * Modal=new  QSqlQueryModel();

                       QSqlQuery query;
                        query.prepare("SELECT* FROM VOYAGES ");
                        query.exec();
                        Modal->setQuery(query);
                       tablevoy.setModel(Modal);



                        db.close();


                        QString strStream;
                        QTextStream out(&strStream);

                        const int rowCount = tablevoy.model()->rowCount();
                        const int columnCount =  tablevoy.model()->columnCount();


                        const QString strTitle ="Document";


                        out <<  "<html>\n"
                            "<head>\n"
                                "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                            <<  QString("<title>%1</title>\n").arg(strTitle)
                            <<  "</head>\n"
                            "<body bgcolor=#ffffff link=#5000A0>\n"
                           << QString("<h3 style=\" font-size: 100px; font-family: Arial, Helvetica, sans-serif; color:#ff0500; font-weight: lighter; text-align: center;\">%1</h3>\n").arg("Liste des Voyages Disponibles")
                           <<"<br>"

                            <<"<table border=2 cellspacing=1 cellpadding=10>\n";

                        out << "<thead><tr bgcolor=#f0f0f0>";
                        for (int column = 0; column < columnCount; column++)
                            if (!tablevoy.isColumnHidden(column))
                                out << QString("<th>%1</th>").arg(tablevoy.model()->headerData(column, Qt::Horizontal).toString());
                        out << "</tr></thead>\n";

                        for (int row = 0; row < rowCount; row++) {
                            out << "<tr>";
                            for (int column = 0; column < columnCount; column++) {
                                if (!tablevoy.isColumnHidden(column)) {
                                    QString data = tablevoy.model()->data(tablevoy.model()->index(row, column)).toString().simplified();
                                    out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                }
                            }
                            out << "</tr>\n";
                        }
                        out <<  "</table>\n"
                                "<br><br>"
                                //<< QString("<p><img src=":/img/aze.png"; width="200"; height="200";\">%1</p>\n")
                                <<"<br>"
                                <<"<table border=1 cellspacing=0 cellpadding=2>\n";


                            out << "<thead><tr bgcolor=#f0f0f0>";

                                out <<  "</table>\n"

                            "</body>\n"
                            "</html>\n";

                        QTextDocument *document = new QTextDocument();
                        document->setHtml(strStream);

                        QPrinter printer;
                        QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                        if (dialog->exec() == QDialog::Accepted) {

                            QLabel lab;
                             QPixmap pixmap(":/img/aze.png");
                            lab.setPixmap(pixmap);
                            QPainter painter(&lab);

                          //  QPrinter printer(QPrinter::PrinterResolution);

                          //  pixmap.load("aze.png");
                           // painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
                            //painter.drawPixmap(10,10,50,50, pixmap);
                            document->print(&printer);
                        }

                        printer.setOutputFormat(QPrinter::PdfFormat);
                        printer.setPaperSize(QPrinter::A4);
                        printer.setOutputFileName("/tmp/commandes.pdf");
                        printer.setPageMargins(QMarginsF(15, 15, 15, 15));



                        delete document;

    }



void MainWindow::on_filtrem_clicked()
{Voyages E;
    ui->tablevoy->setModel(E.afficher(1));
}



void MainWindow::on_filtrep_clicked()
{
    Voyages E;
        ui->tablevoy->setModel(E.afficher(2));
}

void MainWindow::on_adduser_clicked()
{



    int id=B.idgrabber();
            QString status = QString("HASHED TO %1 ").arg(id);
            QMessageBox::information(this, tr("Info"), status);
    QString username=ui->addid->text();

    QString password=ui->addpass->text();

    QString email=ui->addemail->text();

    int admin;
    if(ui->adminch->isChecked()){
       admin=1;
    }else
    {admin=0;
    }



    if (data==""){



QThread::sleep(1);

A.write_to_arduino("1");

QString status6 = QString("adding finger print , red light = take off your finger : "
                          "green light = put your finger , 2 lights up = finger added , 1 red light at the end = failed");
QMessageBox::information(this, tr("Info"), status6);
QByteArray qb;
qb.setNum(id);


A.write_to_arduino(qb);

QString status5 = QString("press ok when finished");
QMessageBox::information(this, tr("Info"), status5);

    bool test=B.ajouter(username,password,admin,email,id);
    if (test){
        QMessageBox::information(nullptr, QObject::tr(" OK"),
                    QObject::tr("Ajout Success.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                    QObject::tr("Ajout failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel); }

}
}
void MainWindow::on_pushsupper_clicked()
{
    QString user=ui->IDSUP->text();

    bool test=B.supp(user);

    if (test){
        QMessageBox::information(nullptr, QObject::tr(" OK"),
                    QObject::tr("suppression avec Success.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                    QObject::tr("suppression failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel); }



}

void MainWindow::on_ban_clicked()
{

    QString user=ui->IDSUP->text();

    bool test=B.bannir(user);

    if (test){
        QMessageBox::information(nullptr, QObject::tr(" OK"),
                    QObject::tr("banned Successfuly.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                    QObject::tr("ban failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel); }

}

void MainWindow::on_afficherstat_clicked()
{

    QT_CHARTS_USE_NAMESPACE
             MainWindow w;

            // Assign names to the set of bars used
             QSqlQuery query;

    query.prepare("SELECT  count (ID) FROM VOYAGES ");
    query.exec();
        int a;
            while(query.next())
            {

                  a = query.value(0).toInt();//Récupère le résultat de la requête


            }

    QBarSet *set0 = new QBarSet("Voyage ajouter");

   *set0 << 2 << 3 << 5 << 3 << 4 << a ;

    QBarSeries *series = new QBarSeries();
    series->append(set0);

    QChart *chart = new QChart();

    // Add the chart
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::AllAnimations);

    // Holds the category titles
    QStringList categories;

    categories<< "Janvier" << "Février" << "Mars"  << "Mai" << "Juin" << "Juillet" ;

    // Adds categories to the axes
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);

    chart->legend()->setAlignment(Qt::AlignBottom);



    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Used to change the palette
    QPalette pal = qApp->palette();

    // Change the color around the chart widget and text
    pal.setColor(QPalette::Window, QRgb(0xff9999));
    pal.setColor(QPalette::WindowText, QRgb(0x660000));

    // Apply palette changes to the application
    qApp->setPalette(pal);

    // Customize the title font
        QFont font;
        font.setPixelSize(40);
        chart->setTitleFont(font);
        chart->setTitleBrush(QBrush(Qt::cyan));
        chart->setTitle("statistique Voyages");

    QMainWindow window;


setCentralWidget(chartView);


}



void MainWindow::on_annulerbt_2_clicked()
{

    QString id;

    id=ui->annchamp->text();
    QSqlQuery query;
    if(ui->radioButton22->isChecked()){
        query.prepare("UPDATE VOYAGES SET ANNULER='1' WHERE ID=:ID");
        query.bindValue(":ID", id);
        query.exec();
    }else
    {query.prepare("UPDATE VOYAGES SET ANNULER='2' WHERE ID=:ID");
        query.bindValue(":ID", id);
        query.exec();
    }
    QMessageBox::information(nullptr, QObject::tr(" OK"),
                QObject::tr("annuler avec success.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_rembbtn_2_clicked()
{
    int calc,rem;
        rem=0;
        QString id;
        id=ui->annchamp->text();


        QSqlQuery query;
        query.prepare("select ANNULER from VOYAGES where ID=:ID");
        query.bindValue(":ID", id);
        query.exec();
        while (query.next()){
            calc=query.value("ANNULER").toUInt();
        }

        if (calc==1){
            rem=-20;
        }else if(calc==2){
            rem=110;
        }


        query.prepare("UPDATE VOYAGES SET REMBOURSEMENT=:REMB WHERE ID=:ID");
        query.bindValue(":ID", id);
        query.bindValue(":REMB", rem);
        query.exec();


        QMessageBox::information(nullptr, QObject::tr(" OK"),
                    QObject::tr("remboursement planifier.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
