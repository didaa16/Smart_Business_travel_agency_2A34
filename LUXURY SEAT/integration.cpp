#include "integration.h"
#include "ui_integration.h"

Integration::Integration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Integration)
{
    ui->setupUi(this);
}

Integration::~Integration()
{
    delete ui;
}
