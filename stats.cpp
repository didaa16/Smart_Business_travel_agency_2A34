/*#include "stats.h"
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

void stats::pie ()
{
    QSqlQuery q1,q2,q3,q4,q5,q6;
        qreal tot=0,c1=0,c2=0,c3=0,c4=0,c5=0;

        q1.prepare("SELECT FROM HOTEL");
        q1.exec();

        q2.prepare("SELECT FROM HOTEL WHERE CLASSE ='1 Etoile'");
        q2.exec();

        q3.prepare("SELECT FROM HOTEL WHERE CLASSE ='2 Etoiles'");
        q3.exec();

        q4.prepare("SELECT FROM HOTEL WHERE CLASSE ='3 Etoiles'");
        q4.exec();

        q5.prepare("SELECT FROM HOTEL WHERE CLASSE ='4 Etoiles'");
        q4.exec();

        q6.prepare("SELECT FROM HOTEL WHERE CLASSE ='5 Etoiles'");
        q4.exec();

        while (q1.next()){tot++;}
        while (q2.next()){c1++;}
        while (q3.next()){c2++;}
        while (q4.next()){c3++;}
        while (q5.next()){c4++;}
        while (q6.next()){c5++;}

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







}*/
