#ifndef MAINWINDOW_FINANCES_H
#define MAINWINDOW_FINANCES_H
#include "facture.h"
#include "arduino_finances.h"
#include <QDialog>
#include <QPrintDialog>
#include <QPrinter>
#include <QApplication>
#include <QtCharts/QLegend>
#include <QtCharts>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
QT_CHARTS_USE_NAMESPACE

QT_BEGIN_NAMESPACE

namespace Ui {
class mainwindow_finances;
}
QT_END_NAMESPACE
class mainwindow_finances : public QDialog
{
    Q_OBJECT

public:
    explicit mainwindow_finances(QWidget *parent = nullptr);
    ~mainwindow_finances();
private slots:
    void on_pushButton_clicked();

    void on_pb_supprimer_clicked();

    void on_pushButton_4_clicked();








    void on_id_rechercher_textChanged(const QString &arg1);

    void on_id_rech_textChanged(const QString &arg1);



    void on_trier_rem_clicked();

    void on_trier_sans_clicked();

    void on_tri_clicked();

    void on_pdf_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_stat_clicked();

private:
    Ui::mainwindow_finances *ui;
    Facture F;
        Facture F1;
        Facture F2;
        Facture F3;
        QByteArray data1; // variable contenant les données reçues

        arduino_finances AF;
};

#endif // MAINWINDOW_FINANCES_H
