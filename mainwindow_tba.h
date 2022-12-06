#ifndef MAINWINDOW_TBA_H
#define MAINWINDOW_TBA_H
#include "client.h"
#include <QtPrintSupport/QPrinter>
#include <QPainter>
#include <QtDebug>
#include <QPdfWriter>
#include <QTextDocument>
#include <QPrintDialog>
#include <QPrinter>
#include <QApplication>
#include <QtCharts/QLegend>
#include <QtCharts>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include "arduino_tba.h"
#include <QDialog>
#include "arduino_tba.h"

namespace Ui {
class mainwindow_tba;
}

class mainwindow_tba : public QDialog
{
    Q_OBJECT

public:
    explicit mainwindow_tba(QWidget *parent = nullptr);
    ~mainwindow_tba();

private slots:


    void on_pushButton_4_clicked();

    void on_le_modifier_clicked();

    void on_pushButton_clicked();



    void on_pushButton_3_clicked();


    void on_le_pdf_clicked();

    void on_le_trier_clicked();

    void on_recherche_id_textChanged(const QString &arg1);

    void on_tab_client_clicked(const QModelIndex &index);

    void on_le_stat_clicked();

    void on_ON_pushButton_0_clicked();

    void on_ON_pushButton_1_clicked();

    void on_ON_pushButton_2_clicked();

    void on_ON_pushButton_3_clicked();

private:
    Ui::mainwindow_tba *ui;
    Client c;
    Client c3;
    Client c1;
QByteArray data;
Arduino_tba A;
};



#endif // MAINWINDOW_TBA_H
