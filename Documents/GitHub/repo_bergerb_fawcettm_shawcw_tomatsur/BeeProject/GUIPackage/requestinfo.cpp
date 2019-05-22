#include "requestinfo.h"
#include "ui_requestinfo.h"

RequestInfo::RequestInfo(Controller _cont,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RequestInfo)
{
    ui->setupUi(this);
    cont = _cont;
}

RequestInfo::~RequestInfo()
{
    delete ui;
}


//the ok button underneath the configuration parameters
void RequestInfo::on_ok_button_clicked()
{
    if(checkInfo()){
    season = ui->season->text().toStdString();
    weather = ui->weather->text().toStdString();
    location = ui->location->text().toStdString();
    temp = ui->temperature->text().toStdString();

    //use these params to find the hive id in the database

    int hiveId = cont.requestWithPara(season,stoi(temp),location);
    if (hiveId == -1) {
        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString("Hive with these configurations does not exist."));
        msgBox.exec();
    }else {

    //display sim
    DisplayInfo *dI = new DisplayInfo(cont.requestWithPara(season,stoi(temp),location),cont);
    dI->show();

    }
    }else{
        Qmsg();
    }
}

int RequestInfo::getHiveId(){
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


//using the hiveId to start the sim
void RequestInfo::on_hiveID_pushButton_clicked()
{
    //use the hive Id to start the sim
    if(!ui->hiveID->text().toStdString().empty()){
        if(stoi(ui->hiveID->text().toStdString()) >cont.maxId()){
            QMessageBox msgBox;
            msgBox.setText(QString::fromStdString("Hive ID does not exist!"));
            msgBox.exec();
        }else{
    hiveId = stoi(ui->hiveID->text().toStdString());
    DisplayInfo *dI = new DisplayInfo(hiveId,cont);
    dI->show();
        }
    }else{
        Qmsg();
    }
}

//error message
void RequestInfo::Qmsg(){
    QMessageBox msgBox;
    msgBox.setText(QString::fromStdString("Please Input all Necessary Parameters!"));
    msgBox.exec();
}

//check that all of the boxes are filled out
bool RequestInfo::checkInfo(){
    if(ui->season->text().toStdString().empty()){
        return 0;
    }
    if(ui->weather->text().toStdString().empty()){
        return 0;
    }
    if(ui->location->text().toStdString().empty()){
        return 0;
    }
    if(ui->temperature->text().toStdString().empty()){
        return 0;
    }
    return 1;
}
