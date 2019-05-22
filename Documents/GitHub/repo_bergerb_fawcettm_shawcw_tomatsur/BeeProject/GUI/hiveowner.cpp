#include "hiveowner.h"
#include "ui_hiveowner.h"

HiveOwner::HiveOwner(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HiveOwner)
{
    ui->setupUi(this);
}

HiveOwner::~HiveOwner()
{
    delete ui;
}


void HiveOwner::on_NewHive_Button_clicked()
{
    ConfigHive *cH = new ConfigHive();
    cH->show();
}

void HiveOwner::on_UpdateHive_Button_clicked()
{
    UpdateHive *uH = new UpdateHive();
    uH->show();
}
