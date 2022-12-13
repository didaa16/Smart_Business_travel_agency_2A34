#ifndef STATS_HOTEL_H
#define STATS_HOTEL_H
#include <QSqlQuery>
#include <QApplication>
#include <QtCharts/QLegend>
#include <QtCharts>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QDialog>

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class stats_hotel;
}

class stats_hotel : public QDialog
{
    Q_OBJECT

public:
    explicit stats_hotel(QWidget *parent = nullptr);
    ~stats_hotel();
    void pie();

private slots:
    void on_pushButton_9_clicked();

private:
    Ui::stats_hotel *ui;
};

#endif // STATS_HOTEL_H
