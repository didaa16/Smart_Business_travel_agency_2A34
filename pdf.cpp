#include "pdf.h"
#include "ui_pdf.h"

Pdf::Pdf(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Pdf)
{
    ui->setupUi(this);
}

Pdf::~Pdf()
{
    delete ui;
}
