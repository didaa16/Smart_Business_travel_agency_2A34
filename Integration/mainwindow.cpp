#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    hotel = new mainwindow_hotel ();
    hotel->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    finance = new mainwindow_finances ();
    finance ->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    visa=new mainwindow_visa();
    visa->show();
}

void MainWindow::on_pushButton_4_clicked()
{
    c = new mainwindow_tba();
    c->show();
}

void MainWindow::on_pushButton_5_clicked()
{
    v = new MainWindow_voyage();
    v->show();
}
