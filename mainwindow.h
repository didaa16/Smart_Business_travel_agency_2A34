#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "facture.h"
#include <QMainWindow>

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
    void on_pushButton_clicked();

    void on_pb_supprimer_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    Facture F;
};
#endif // MAINWINDOW_H
