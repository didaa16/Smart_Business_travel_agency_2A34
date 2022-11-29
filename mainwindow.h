#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "hotel.h"
#include "stats.h"
#include <QMainWindow>
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
#include "arduino.h"

QT_CHARTS_USE_NAMESPACE
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_5_clicked(); //AJOUT

    void on_pushButton_2_clicked(); //SUPPRESSION

    void on_pushButton_clicked(); //MODIFIER

    void on_tabaffichage_clicked(const QModelIndex &index); //SELECTION FROM TABLE VIEW

    void on_linecomboBox_currentIndexChanged(int index); //TRIER COMBOBOX

    void on_lineEdit_342_textChanged(const QString &arg1); // RECHERCHE

    void on_pushButton_8_clicked(); // RECOMMENDATION

    void on_pushButton_pdf_clicked(); // PDF

    void on_actionAjouter_triggered(); //BOUTON AJOUTER

    void on_actionPdf_triggered(); //BOUTON PDF

    void on_actionAfficher_triggered(); //BOUTON AFFICHER

    void on_actionLuxury_Seat_triggered(); //BOUTON LOGO

    void on_actionRecommender_triggered();//BOUTON RECOMMENDER

    void on_actionStatiqtiques_triggered();//STATS

    void on_actionQuitter_triggered(); //BOUTON QUITTER

    void on_pushButton_4_clicked(); //RETOUR D'AFFICHER

    void on_pushButton_11_clicked(); //RETOUR DE RECOMMENDATION

    void on_pushButton_10_clicked(); //RETOUR DE PDF

    void on_tabWidget_tabCloseRequested(int index); //REMOVE TAB

    void on_pushButton_6_clicked(); //ANNULER D'AJOUT


private:
    Ui::MainWindow *ui;
    stats *s;
    Hotel Htmp;
    QByteArray data; // variable contenant les données reçues
    Arduino A;
};

#endif // MAINWINDOW_H
