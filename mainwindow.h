#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "facturee.h"
#include <QMainWindow>
#include <QPrintDialog>
#include <QPrinter>
#include <QApplication>
#include <QtCharts/QLegend>
#include <QtCharts>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include "arduino.h"
QT_CHARTS_USE_NAMESPACE

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_pd_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_id_rechercher_textChanged(const QString &arg1);

    void on_id_recherche_s_textChanged(const QString &arg1);

    void on_trier_clicked();

    void on_trier_s_clicked();

    void on_trier_r_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pb_pdf_clicked();

    void on_pb_stat_clicked();



private:
    Ui::MainWindow *ui;
    Facturee M;
    Facturee M1;
    Facturee M2;
    Facturee M3;
int montant_apres_remise;
QString name;

QByteArray data; // variable contenant les données reçues

   Arduino A; // objet temporaire
};
#endif // MAINWINDOW_H
