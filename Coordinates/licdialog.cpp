#include "licdialog.h"
#include "ui_licdialog.h"

licDialog::licDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::licDialog)
{
    ui->setupUi(this);
}

licDialog::~licDialog()
{
    delete ui;
}
