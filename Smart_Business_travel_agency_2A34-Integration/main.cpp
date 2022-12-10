#include "mainwindow.h"
#include "connection.h"
#include "loginwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QTranslator>
#include <QInputDialog>
#include "connection.h"
#include <QApplication>
#include <QWidget>
#include <QDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    bool test =c.createconnect();
    MainWindow w;
    loginwindow login;
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    login.show();
    return a.exec();
}
