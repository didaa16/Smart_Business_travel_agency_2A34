#ifndef MAINWINDOW_HOTEL_H
#define MAINWINDOW_HOTEL_H

#include <QDialog>
#include "arduino_hotel.h"
#include "hotel.h"
#include "stats_hotel.h"
#include "connection.h"
#include <QSqlQueryModel>
#include <QDebug>
#include <QSqlQuery>
#include <QApplication>
#include <QtCharts/QLegend>
#include <QtCharts>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QPrinter>
#include <QPrintDialog>

QT_CHARTS_USE_NAMESPACE
namespace Ui {
class mainwindow_hotel;
}

class mainwindow_hotel : public QDialog
{
    Q_OBJECT

public:
    explicit mainwindow_hotel(QWidget *parent = nullptr);
    ~mainwindow_hotel();

private slots:
    void on_pushButton_7_clicked(); //AJOUT

    void on_pushButton_13_clicked(); //SUPPRIMER

    void on_pushButton_12_clicked(); //MODIFIER

    void on_affichage_clicked(const QModelIndex &index); //AFFICHER FROM TABLE

    void on_rechercher_textChanged(const QString &arg1); //RECHRCHER

    void on_linecomboBox_5_currentIndexChanged(int index); //TRI

    void on_pushButton_16_clicked(); // RECOMMENDATION

    void on_pushButton_pdf_2_clicked(); // PDF

    void on_pushButton_14_clicked(); //BOUTON STATS

    void on_pushButton_9_clicked(); //RETOUR D'AJOUT

    void on_pushButton_19_clicked(); // RETOUR D'AFFICHER

    void on_pushButton_17_clicked(); //RETOUR DE RECOMMENDATION

    void on_pushButton_18_clicked(); //RETOUR DE PDF

private:
    Ui::mainwindow_hotel *ui;
    stats_hotel *s;
    Hotel Htmp;
    QByteArray data;
    arduino_hotel A;
};

#endif // MAINWINDOW_HOTEL_H
