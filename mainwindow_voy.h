#ifndef MAINWINDOW_VOY_H
#define MAINWINDOW_VOY_H

#include <voyages.h>
//#include <login.h>
#include <QMainWindow>
//#include "arduino.h"
//#include "arduinouno.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow_voy; }
QT_END_NAMESPACE

class MainWindow_voy : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow_voy(QWidget *parent = nullptr);
    ~MainWindow_voy();




private slots:
    void update_label();
    void on_addbutt_clicked();

    void on_pbsupp_clicked();

    void on_pushsupp_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_rechbtt_clicked();

    void on_EXPORTING_clicked();

    void on_newpp_clicked();

    void on_filtrem_clicked();

    void on_filtrep_clicked();

    void on_adduser_clicked();

    void on_pushsupper_clicked();

    void on_ban_clicked();

    void on_afficherstat_clicked();

    void on_annulerbt_clicked();

    void on_rembbtn_clicked();

    void on_annulerbt_2_clicked();

    void on_rembbtn_2_clicked();

private:
    Ui::MainWindow_voy *ui;
    Voyages E;
    //Login B;
   // arduino A;
    QByteArray data;
    //arduino1 A1;
    QByteArray data1;

};

#endif // MAINWINDOW_VOY_H
