#include "updatehive.h"
#include "ui_updatehive.h"

UpdateHive::UpdateHive(Controller _cont,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateHive)
{
    ui->setupUi(this);
    cont = _cont;
}

UpdateHive::~UpdateHive()
{
    delete ui;
}


void UpdateHive::on_pushButton_clicked()
{
    hiveId = ui->HiveID->text().toStdString();
}
