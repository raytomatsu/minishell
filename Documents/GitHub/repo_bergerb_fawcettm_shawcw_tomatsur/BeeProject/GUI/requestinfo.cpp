#include "requestinfo.h"
#include "ui_requestinfo.h"

RequestInfo::RequestInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RequestInfo)
{
    ui->setupUi(this);
}

RequestInfo::~RequestInfo()
{
    delete ui;
}

void RequestInfo::on_ok_button_clicked()
{
    season = ui->season->text().toStdString();
    weather = ui->weather->text().toStdString();
    location = ui->location->text().toStdString();
    temp = ui->temperature->text().toStdString();
}

string RequestInfo::getHiveId(){
    return hiveId;
}

string RequestInfo::getSeason(){
    return season;
}

string RequestInfo::getWeather(){
    return weather;
}

string RequestInfo::getLocation(){
    return location;
}

void RequestInfo::on_hiveID_pushButton_clicked()
{
    hiveId = ui->hiveID->text().toStdString();
}
