#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include "mainwindow.h"

#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
class loginwindow;
}

class loginwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit loginwindow(QWidget *parent = nullptr);
    ~loginwindow();

private slots:
    void on_loginbar_clicked();

     void on_codesender_clicked();


private:
    Ui::loginwindow *ui;
    MainWindow* mainwindow;
    Login B;
};

#endif // LOGINWINDOW_H
