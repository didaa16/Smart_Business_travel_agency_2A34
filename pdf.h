#ifndef PDF_H
#define PDF_H

#include <QDialog>

namespace Ui {
class Pdf;
}

class Pdf : public QDialog
{
    Q_OBJECT

public:
    explicit Pdf(QWidget *parent = nullptr);
    ~Pdf();

private:
    Ui::Pdf *ui;
};

#endif // PDF_H
