#ifndef MAINWINDOW_VOYAGE_H
#define MAINWINDOW_VOYAGE_H

#include <QMainWindow>
#include <voyages.h>
#include <login.h>

#include <QMainWindow>


namespace Ui {
class MainWindow_voyage;
}

class MainWindow_voyage : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_voyage(QWidget *parent = nullptr);
    ~MainWindow_voyage();

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
    Ui::MainWindow_voyage *ui;
    Voyages E;
    Login B;
    //arduino A;
    QByteArray data;
    //arduino1 A1;
    QByteArray data1;



};

#endif // MAINWINDOW_VOYAGE_H
