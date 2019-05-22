#include "researcher.h"
#include "ui_researcher.h"

Researcher::Researcher(Controller _cont,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Researcher)
{
    ui->setupUi(this);
    cont = _cont;
}

Researcher::~Researcher()
{
    delete ui;
}


/**
 * Researcher can either request info or configure a hive. this allows them to generate and also analyze data
 */


void Researcher::on_requestInfo_Button_clicked()
{
    RequestInfo *rI = new RequestInfo(cont);
    rI->show();
}

void Researcher::on_configureNewHive_Button_clicked()
{
    ConfigHive *cH = new ConfigHive(cont);
    cH->show();
}

void Researcher::on_pushButton_clicked()
{
    RequestGraph *rG = new RequestGraph(cont);
    rG->show();
}
