#include "hiveowner.h"
#include "ui_hiveowner.h"

HiveOwner::HiveOwner(Controller _cont,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HiveOwner)
{
    ui->setupUi(this);
    cont = _cont;
}

HiveOwner::~HiveOwner()
{
    delete ui;
}


/**
 * HiveOwner can either request info or configure a hive. Configuring would mean to simulate their hive, and update hive would show them
 * the sim of their hives activity
 */


void HiveOwner::on_NewHive_Button_clicked()
{
    ConfigHive *cH = new ConfigHive(cont);
    cH->show();
}

void HiveOwner::on_UpdateHive_Button_clicked()
{
    RequestInfoOneHive *uH = new RequestInfoOneHive(cont);
    uH->show();
}
