#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <QDialog>

namespace Ui {
class Integration;
}

class Integration : public QDialog
{
    Q_OBJECT

public:
    explicit Integration(QWidget *parent = nullptr);
    ~Integration();

private:
    Ui::Integration *ui;
};

#endif // INTEGRATION_H
