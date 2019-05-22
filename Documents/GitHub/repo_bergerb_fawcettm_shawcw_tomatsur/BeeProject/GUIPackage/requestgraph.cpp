#include "requestgraph.h"
#include "ui_requestgraph.h"
#include <iostream>

RequestGraph::RequestGraph(Controller cont, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RequestGraph)
{
    ui->setupUi(this);
    this->cont = cont;
}

RequestGraph::~RequestGraph()
{
    delete ui;
}


void RequestGraph::on_ok_button_clicked()
{

    if(!checkInfo()){
        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString("Hive with these configurations does not exist."));
        msgBox.exec();
    }else{
    int hiveId1 = cont.requestWithPara(ui->season->text().toStdString(),stoi(ui->temperature->text().toStdString()),ui->location->text().toStdString());
    int hiveId2 = cont.requestWithPara(ui->season_2->text().toStdString(),stoi(ui->temperature_2->text().toStdString()),ui->location_2->text().toStdString());


    if(hiveId1 == -1|| hiveId2== -1){
        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString("Hive with these configurations does not exist."));
        msgBox.exec();
    }else{
    generate(cont.requestWithId(hiveId1)->get_list());
    cout << "Between" << endl;
    generate2(cont.requestWithId(hiveId2)->get_list());
    GraphsMulti *gM = new GraphsMulti(changeOne,timeOne,changeTwo,timeTwo);
    gM->show();
    }
    }
}

void RequestGraph::generate(vector<Event*> events){
    int index = 1;
    int entries = 0;
    int peak = 0;
    int exits = 0;

    while(index<events.size()){
        std::string event = events[index]->getType();
        long long time = events[index]->getTime();
    if(event.compare("Entry") == 0){
        entries++;
        cout << entries;
    }else if(event.compare("Peek")==0){
        peak++;
    }else {
        exits++;
    }
    changeOne.push_back(entries - exits);
    timeOne.push_back(events[index]->getTime());
    index++;
    }
}

void RequestGraph::generate2(vector<Event*> events){
    int index = 1;
    int entries = 0;
    int peak = 0;
    int exits = 0;

    while(index<events.size()){
        std::string event = events[index]->getType();
        long long time = events[index]->getTime();
    if(event.compare("Entry") == 0){
        entries++;
        cout << entries;
    }else if(event.compare("Peek")==0){
        peak++;
    }else {
        exits++;
    }
    changeTwo.push_back(entries - exits);
    timeTwo.push_back(events[index]->getTime());
    index++;
    }
}

bool RequestGraph::checkInfo(){
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
    if(ui->season_2->text().toStdString().empty()){
        return 0;
    }
    if(ui->weather_2->text().toStdString().empty()){
        return 0;
    }
    if(ui->location_2->text().toStdString().empty()){
        return 0;
    }
    if(ui->temperature_2->text().toStdString().empty()){
        return 0;
    }
    return 1;
}
