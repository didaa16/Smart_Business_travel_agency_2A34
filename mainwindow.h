#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "gestionvisa.h"

#include <QMainWindow>
#include <QStandardItemModel>
#include <QApplication>
#include <QtCharts/QLegend>
#include <QtCharts>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

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
private:
     gestionvisa a;
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();
    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_lineEdit_12_textChanged(const QString &arg1);

    void on_pushButton_7_clicked();

    void on_tableView_2_clicked(const QModelIndex &index);

    void on_pushButton_15_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;

};
#endif // MAINWINDOW_H
