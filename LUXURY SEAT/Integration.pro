QT += core gui
QT += core gui sql
QT += core gui printsupport
QT += core gui charts
QT += serialport
QT       += core gui  network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    alerte.cpp \
    arduino_finances.cpp \
    arduino_hotel.cpp \
    arduino_tba.cpp \
    client.cpp \
    connection.cpp \
    facture.cpp \
    gestionvisa.cpp \
    hotel.cpp \
    login.cpp \
    loginwindow.cpp \
    mailsender.cpp \
    main.cpp \
    mainwindow.cpp \
    mainwindow_finances.cpp \
    mainwindow_hotel.cpp \
    mainwindow_tba.cpp \
    mainwindow_visa.cpp \
    mainwindow_voyage.cpp \
    smtpp.cpp \
    stats_hotel.cpp \
    voyages.cpp

HEADERS += \
    alerte.h \
    arduino_finances.h \
    arduino_hotel.h \
    arduino_tba.h \
    client.h \
    connection.h \
    facture.h \
    gestionvisa.h \
    hotel.h \
    login.h \
    loginwindow.h \
    mailsender.h \
    mainwindow.h \
    mainwindow_finances.h \
    mainwindow_hotel.h \
    mainwindow_tba.h \
    mainwindow_visa.h \
    mainwindow_voyage.h \
    smtpp.h \
    stats_hotel.h \
    voyages.h

FORMS += \
    loginwindow.ui \
    mainwindow.ui \
    mainwindow_finances.ui \
    mainwindow_hotel.ui \
    mainwindow_tba.ui \
    mainwindow_visa.ui \
    mainwindow_voyage.ui \
    stats_hotel.ui

TRANSLATIONS += \
    Integration_en_001.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Ressources.qrc
