#include "teacher.h"
#include "ui_teacher.h"

Teacher::Teacher(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Teacher)
{
    ui->setupUi(this);
}

Teacher::~Teacher()
{
    delete ui;
}

void Teacher::on_requestInfo_Button_clicked()
{
    RequestInfo *rI = new RequestInfo();
    rI->show();
}

void Teacher::on_configureNewHive_Button_clicked()
{
    ConfigHive *cH = new ConfigHive();
    cH->show();
}
