#include "Finished.h"
#include "ui_Finished.h"

Finished::Finished(QWidget *parent) :
    QDialog(parent),
    ui(new Ui_Dialog)
{
    ui->setupUi(this);
}

Finished::~Finished()
{
    delete ui;
}
