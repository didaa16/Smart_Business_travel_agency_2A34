#ifndef HOTEL_H
#define HOTEL_H

#include <QString>
#include <QList>
#include <QSqlQueryModel>
#include <QDebug>
#include <QSqlQuery>
#include <QVector>
#include <QDialog>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

QT_CHARTS_USE_NAMESPACE

class Hotel
{
private:
    int id;
    long num;
    float prix;
    QString nom, adresse, classe;
    QList <int> reco;
    QList <QString> tabadresse;
public:
    Hotel ();
    Hotel(int, QString, QString, long, float, QString);
    int get_id ();
    QString get_nom();
    QString get_adresse ();
    long get_num ();
    float get_prix ();
    QString get_classe ();
    QList <int> get_reco ();
    QList <QString> get_tabadresse();
    void set_id (int);
    void set_nom (QString);
    void set_adresse (QString);
    void set_num (long);
    void set_prix (float);
    void set_classe (QString);
    void set_reco (int);
    void set_tabadresse (QString);
    bool ajouter();
    QSqlQueryModel *afficher ();
    bool supprimer (int);
    bool rechercher (int);
    bool modifier();
    bool modifier_classe();
    int calcul_adresses(QString);
    void pie();
    QStringList listeadresses();
    QSqlQueryModel *afficherrecherche (QString);
    QString classification();
};

#endif // HOTEL_H
