#include "displayinfo.h"
#include "ui_displayinfo.h"
#include <QInputDialog>
#include <cmath>
#include <iostream>
using namespace std;
using namespace chrono;


DisplayInfo::DisplayInfo(int _hiveId,Controller _cont,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DisplayInfo)
{
    ui->setupUi(this);
    hiveId = _hiveId;
    cont = _cont;


    userSpeed();


    ui->warning->setStyleSheet("font-weight: bold; color: red; font-size: 24pt;font-family: Didot");

    //request all of the events for this hive
    events = cont.requestWithId(hiveId)->get_list();
    std::string* details = cont.retrieve_config_details(hiveId);
    //keep track of season, affects swarm and robbery
    season = details[0];
    temp = stoi(details[1]);
    entries = 0;
    exits = 0;
    peak = 0;
    index =1;
    netChange = 0;
    netChangeArray = vector<int>();
    startSimulation();
}


//allow user to choose speef
void DisplayInfo::userSpeed(){
    setStyleSheet("QInputDialog {font-family: Didot;};");
    QStringList items;
    items << tr("Normal") << tr("10x speed") << tr("100x speed") << tr("500x speed");
    QString qitem = QInputDialog::getItem(this, tr("QInputDialog::getItem()"),
                                         tr("How Fast Would you like your simulation to go?"), items, 0, false);
  //set the speeds for the sim
    string item = qitem.toStdString();
    if(item.compare("Normal")==0){
        sf =1;
    }else if(item.compare("10x speed")==0){
        sf = 0.1;
    }else if(item.compare("100x speed")==0){
        sf = 0.001;
    }else{
        sf = 0.002;
    }
    return;
}

DisplayInfo::~DisplayInfo()
{
    delete ui;
}

//updates every time step. changes label based on the event
void DisplayInfo::updateLabel() {
    std::string event = events[index]->getType();
    long long time = events[index]->getTime();
    tm* hourmin = translateTime(time);
    int hour = hourmin->tm_hour;
    int min = hourmin->tm_min;
    int sec = hourmin->tm_sec;

    //update numbers of entries exits and peaks
    if(event.compare("Entry") == 0){
        entries++;
        updateEntry(entries);
    }else if(event.compare("Peek")==0){
        peak++;
        updatePeak(peak);
    }else {
        exits++;
        updateExit(exits);
    }
    updateTime(hour, min, sec);

    //every time step, check for a warning
    checkWarning();
    index++;

    //stop at the last event
    if(index == events.size()){
        timer->stop();
    }
}


//check for a swarm or robbery warning
void DisplayInfo::checkWarning(){
    //keep treack of net change for the graph
    netChange = entries - exits;
    netChangeArray.push_back(netChange);

    //keep track of times for the graph
    time.push_back(events[index]->getTime());
        //show a swarm warning
    if(cont.check_for_swarm(entries,exits,season, temp)){
            ui->warningSign->setPixmap(QPixmap(":/img/warning2.png" ) );
            ui->warningSign->setScaledContents(true);
            ui->warningSign->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        ui->warning->setText("SWARM WARNING!");
        //show a robbery warning
    }else if(cont.check_for_robbery(entries,exits,season, temp)){
            ui->warningSign->setPixmap(QPixmap(":/img/warning2.png" ) );
            ui->warningSign->setScaledContents(true);
            ui->warningSign->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        ui->warning->setText("ROBBERY WARNING!");
        //get rid of it
    }else{
         ui->warningSign->clear();
        ui->warning->setText("");
    }
}

//timer. takes into account the interval as well as the speed variable
void DisplayInfo::startSimulation(){
    //the array of time intervals
        vector <long long> dif = extract_times();
        double span = dif.at(index)*sf;
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(updateLabel()));
        timer->start(span);
}


//create the time differences
vector<long long> DisplayInfo::extract_times() {
    vector <long long> dif;
    //subtract the last event from this event
    for(int i = 1; i<events.size(); i++){
        dif.push_back(events.at(i)->getTime() - events.at(i-1)->getTime());
    }
    return dif;
}

void DisplayInfo::updateEntry(int t){
    ui->Entries->setStyleSheet("font-family: Didot");
    ui->Entries->setText(QString::number(t));
}

void DisplayInfo::updateExit(int t){
    ui->Exits->setStyleSheet("font-family: Didot");
    ui->Exits->setText(QString::number(t));
}

void DisplayInfo::updateTime(int hour, int min, int sec){
    ui->Time->setStyleSheet("font-family: Didot");
    ui->Time->setText(QString::number(hour) + ":" + QString::number(min) + ":" + QString::number(sec));
}

void DisplayInfo::updatePeak(int t){
    ui->Peaks->setStyleSheet("font-family: Didot");
    ui->Peaks->setText(QString::number(t));
}

//show the graph
void DisplayInfo::on_pushButton_clicked()
{
    Graph *g = new Graph(time,netChangeArray);
    g->show();
}

tm* DisplayInfo::translateTime(long long time) {
    long long int milliSecondsSinceEpoch =  time;
    const auto durationSinceEpoch = std::chrono::milliseconds(milliSecondsSinceEpoch);
    const time_point<system_clock> tp_after_duration(durationSinceEpoch);
    time_t time_after_duration = system_clock::to_time_t(tp_after_duration);

    std::tm* formattedTime = localtime(&time_after_duration);

    return formattedTime;
}
