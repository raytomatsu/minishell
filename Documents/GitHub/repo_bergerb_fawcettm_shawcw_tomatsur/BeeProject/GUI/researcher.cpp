#include "researcher.h"
#include "ui_researcher.h"

Researcher::Researcher(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Researcher)
{
    ui->setupUi(this);
}

Researcher::~Researcher()
{
    delete ui;
}


void Researcher::on_requestInfo_Button_clicked()
{
    RequestInfo *rI = new RequestInfo();
    rI->show();
}

void Researcher::on_configureNewHive_Button_clicked()
{
    ConfigHive *cH = new ConfigHive();
    cH->show();
}
