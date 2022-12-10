#ifndef MAINWINDOW_VISA_H
#define MAINWINDOW_VISA_H
#include "gestionvisa.h"


#include <QStandardItemModel>
#include <QApplication>
#include <QtCharts/QLegend>
#include <QtCharts>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QDialog>
QT_CHARTS_USE_NAMESPACE

QT_BEGIN_NAMESPACE
namespace Ui {
class mainwindow_visa;
}
QT_END_NAMESPACE
class mainwindow_visa : public QDialog
{
    Q_OBJECT

public:
    explicit mainwindow_visa(QWidget *parent = nullptr);
    ~mainwindow_visa();
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
    Ui::mainwindow_visa *ui;
      QStandardItemModel *model;
};

#endif // MAINWINDOW_VISA_H
