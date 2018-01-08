#ifndef LICDIALOG_H
#define LICDIALOG_H

#include <QDialog>

namespace Ui {
class licDialog;
}

class licDialog : public QDialog
{
    Q_OBJECT

public:
    explicit licDialog(QWidget *parent = 0);
    ~licDialog();

private:
    Ui::licDialog *ui;
};

#endif // LICDIALOG_H
