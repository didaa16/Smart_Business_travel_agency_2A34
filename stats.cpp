#include "stats.h"
#include "ui_stats.h"

stats::stats(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stats)
{
    ui->setupUi(this);
}

stats::~stats()
{
    delete ui;
}
 void stats::pie()
 {
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
     q2.prepare("Select * from Hotel where classe ='1'");
     if(q2.exec())
     {
         while (q2.next())
         {
             c1++;
         }
     }
     q3.prepare("Select * from Hotel where classe ='2'");
     if(q3.exec())
     {
         while (q3.next())
         {
             c2++;
         }
     }
     q4.prepare("Select * from Hotel where classe ='3'");
     if(q4.exec())
     {
         while (q4.next())
         {
             c3++;
         }
     }
     q5.prepare("Select * from Hotel where classe ='4'");
     if(q5.exec())
     {
         while (q5.next())
         {
             c4++;
         }
     }
     q6.prepare("Select * from Hotel where classe ='5'");
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
             series->append("1",c1);
             series->append("2",c2);
             series->append("3",c3);
             series->append("4",c4);
             series->append("5",c5);
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
             ui->stat->setLayout(layout);
 }

void stats::on_pushButton_9_clicked()
{
    stats::hide();
}
