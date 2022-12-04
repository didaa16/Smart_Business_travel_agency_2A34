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
