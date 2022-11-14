#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QSqlQuery>
#include<QMessageBox>
#include <QSqlQueryModel>
#include <QDesktopServices>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include "mail.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_25->setValidator(new QIntValidator(0, 99999999, this));
    ui->lineEdit_12->setValidator(new QIntValidator(0, 99999999, this));
    ui->lineEdit_9->setValidator(new QIntValidator(0, 99999999, this));
    ui->lineEdit_6->setValidator(new QIntValidator(0, 99999999, this));
    ui->lineEdit_3->setValidator(new QIntValidator(0, 99999999, this));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{
    QString num_de_passeporte=ui->lineEdit->text();
    QString num_de_compte_bancaire=ui->lineEdit_2->text();
    QString cin=ui->lineEdit_3->text();
     QString mail=ui->lineEdit_4->text();
    QString destination=ui->comboBox->currentText();
    //QString acp_auto="0";
    QSqlQuery qry;
    qry.prepare("INSERT INTO VISA (num_de_passeporte, num_de_compte_bancaire, destination,cin,mail) "
                "VALUES (:num_de_passeporte,:num_de_compte_bancaire,:destination, :cin,:mail)");
    qry.bindValue(":num_de_passeporte",num_de_compte_bancaire);
    qry.bindValue(":num_de_compte_bancaire",num_de_compte_bancaire );
    qry.bindValue(":cin",cin);
    qry.bindValue(":mail",mail);
    qry.bindValue(":destination",destination);
    if(qry.exec())
    {QMessageBox::information(this,"edit","service added successfully");}
    else
    {QMessageBox::warning(this,"error","error");}
}

void MainWindow::on_pushButton_3_clicked()
{
    QSqlQuery req;
       model=new QStandardItemModel(5,5);
       int row=0;
       req.exec("select num_de_passeporte,num_de_compte_bancaire,cin,mail,destination from visa");
       while(req.next())
       {
           for(int i=0;i<6;i++)
           {
               QStandardItem *item=new QStandardItem(req.value(i).toString());   //i le nombre de colone;
               model->setItem(row,i,item);
           }
           row++;

       }

       model->setHeaderData(0,Qt::Horizontal,"N°passeport");
       model->setHeaderData(1,Qt::Horizontal,"N°compte_bancaire");//ecrire header of table
       model->setHeaderData(2,Qt::Horizontal,"cin");
       model->setHeaderData(3,Qt::Horizontal,"mail");
       model->setHeaderData(4,Qt::Horizontal,"destination");


       ui->tableView->setModel(model);
}

void MainWindow::on_pushButton_4_clicked()
{
    QString cin=ui->lineEdit_6->text();
    QSqlQuery qry;
        qry.prepare("Delete from visa where cin='"+cin+"'");
                if(qry.exec())
                {
                  QMessageBox::critical(this,"delete","deleted");
                }
                else
                {
                    QMessageBox::critical(this,"error","not deleted");
                }

}

void MainWindow::on_pushButton_clicked()
{
    QString num_de_passeporte=ui->lineEdit_7->text();
        QString num_de_compte_bancaire=ui->lineEdit_8->text();
        QString cin=ui->lineEdit_9->text();
        QString email=ui->lineEdit_10->text();
        QString destination=ui->comboBox_2->currentText();

        QSqlQuery qry;
        qry.prepare("update visa set  num_de_passeporte='"+num_de_passeporte+"',num_de_compte_bancaire='"+num_de_compte_bancaire+"',cin='"+cin+"',mail='"+email+"',destination='"+destination+"'where  cin='"+cin+"' " );
        if(qry.exec())
        {

            QMessageBox::critical(this,"edit","updated");
        }
        else
        {
            QMessageBox::critical(this,"error"," not updated");

        }

}
void MainWindow::on_pushButton_5_clicked()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("Select * from VISA ORDER BY DESTINATION DESC");
    ui->tableView->setModel(model);
}

void MainWindow::on_pushButton_6_clicked()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("Select * from VISA ORDER BY DESTINATION ASC");
    ui->tableView->setModel(model);
}

void MainWindow::on_lineEdit_12_textChanged(const QString &arg1)
{
    ui->tableView_2->setModel(a.chercher(arg1));
}
void MainWindow::on_pushButton_7_clicked()
{
    QPrinter printer;
    printer.setPrinterName("VISA");
    QPrintDialog dialog(&printer,this);
    if (dialog.exec() == QDialog::Rejected) return;
    ui->textEdit->print(&printer);

}

void MainWindow::on_tableView_2_clicked(const QModelIndex &index)
{

    QString val=ui->tableView_2->model()->data(index).toString();
        QSqlQuery qry;
        qry.prepare("select * from VISA where CIN=:val");
        qry.bindValue(":val",val);
        if (qry.exec())
        {
            while(qry.next())
            {
                QString s=(qry.value(0).toString()+"\n"+qry.value(1).toString()+"\n"+qry.value(2).toString()+"\n"+qry.value(3).toString()+"\n"+qry.value(4).toString());
                ui->textEdit->setText(s);
            }
        }
            else
            {
               QMessageBox::warning(this,"error","no information");
            }
}

void MainWindow::on_pushButton_15_clicked()
{
    QString val,x;

     x="0";
     ui->lineEdit_26->setText(x);

    val=ui->lineEdit_25->text();
    QSqlQuery qry;
    qry.prepare("SELECT * FROM VISA WHERE CIN=:val");
    qry.bindValue(":val",val);
         if (qry.exec())
          {
             while(qry.next())
             {
               x="1";
               ui->lineEdit_26->setText(x);
               QMessageBox::warning(this,"validé","felicitation");
             }
             /*x="0";
              ui->lineEdit_26->setText(x);
              QMessageBox::warning(this,"erreur","wrong information");*/
         }
          else
             {
                 QMessageBox::warning(this,"erreur","wrong information");
             }

}


void MainWindow::on_pushButton_8_clicked()
{
    QSqlQuery q1,q2,q3,q4,q5,q6;
        qreal total=0,c1=0,c2=0,c3=0,c4=0,c5=0;
        q1.prepare("Select * from VISA");
        if(q1.exec())
        {
            while (q1.next())
            {
                total++;
            }
        }
        q2.prepare("Select * from VISA where destination ='france'");
        if(q2.exec())
        {
            while (q2.next())
            {
                c1++;
            }
        }
        q3.prepare("Select * from VISA where destination ='turkey'");
        if(q3.exec())
        {
            while (q3.next())
            {
                c2++;
            }
        }
        q4.prepare("Select * from VISA where destination ='germany'");
        if(q4.exec())
        {
            while (q4.next())
            {
                c3++;
            }
        }
        q5.prepare("Select * from VISA where destination ='italy'");
        if(q5.exec())
        {
            while (q5.next())
            {
                c4++;
            }
        }
        q6.prepare("Select * from VISA where destination ='spain'");
        if(q6.exec())
        {
            while (q6.next())
            {
                c5++;
            }
        }
        c1=c1/total;
        c2=c2/total;
        c3=c3/total;
        c4=c4/total;
        c5=c5/total;

        QPieSeries *series = new QPieSeries();

                series->append("france",c1);
                series->append("turkey",c2);
                series->append("germany",c3);
                series->append("italy",c4);
                series->append("spain",c5);

                QPieSlice *slice0 = series->slices().at(0);

                slice0->setExploded();
                slice0->setLabelVisible();
                slice0->setPen(QPen(Qt::darkRed, 2));
                slice0->setBrush(Qt::red);

                QPieSlice *slice1 = series->slices().at(1);

                slice1->setExploded();
                slice1->setLabelVisible();
                slice1->setPen(QPen(Qt::darkMagenta, 2));
                slice1->setBrush(Qt::magenta);

                QPieSlice *slice2 = series->slices().at(2);

                slice2->setExploded();
                slice2->setLabelVisible();
                slice2->setPen(QPen(Qt::darkBlue, 2));
                slice2->setBrush(Qt::blue);

                QPieSlice *slice3 = series->slices().at(3);

                slice3->setExploded();
                slice3->setLabelVisible();
                slice3->setPen(QPen(Qt::darkYellow, 2));
                slice3->setBrush(Qt::yellow);

                QPieSlice *slice4 = series->slices().at(4);

                slice4->setExploded();
                slice4->setLabelVisible();
                slice4->setPen(QPen(Qt::darkCyan, 2));
                slice4->setBrush(Qt::cyan);

                QChart *chart = new QChart();

                chart->addSeries(series);
                chart->setTitle("les pays les plus visitées");
                chart->setAnimationOptions(QChart::AllAnimations);
                chart->legend()->hide();

                QChartView *chartView = new QChartView(chart);
                chartView->setRenderHint(QPainter::Antialiasing);
                QGridLayout *layout = new QGridLayout();
                layout->addWidget(chartView);
                ui->statistique->setLayout(layout);
}

void MainWindow::on_pushButton_9_clicked()
{
    Smtp* smtp = new Smtp("medamine.daboussi@esprit.tn","211JMT3641","smtp.gmail.com",465);
      connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
        smtp->sendMail("medamine.daboussi@esprit.tn", ui->lineEdit_15->text() , ui->lineEdit_17->text(),ui->textEdit_2->toPlainText());
        QMessageBox::information(nullptr, QObject::tr(" OK"),
                            QObject::tr("mail sent Successfuly.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
}
