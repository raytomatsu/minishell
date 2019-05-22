#include "confighive.h"
#include "ui_confighive.h"

ConfigHive::ConfigHive(Controller _cont,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigHive)
{
    ui->setupUi(this);
    QObject::connect(qnam, &QNetworkAccessManager::finished, this, &ConfigHive::fin);
    cont = _cont;

}


void ConfigHive::on_ok_button_clicked()
{

    //manual input of parameteres
    if(ui->longitude->text().toStdString().empty()){
        string state;
        switch(ui->UserBox->currentIndex()){
        case 0: {
            state = "robbery";
            break;
        }
        case 1:{
            state = "swarm";
            break;
        }
        case 2:{
            state = "normal";
            break;
        }
        }
        switch(ui->UserBox->currentIndex()){
        case 0: {
            season = "spring";
            break;
        }
        case 1:{
            season = "summer";
            break;
        }
        case 2:{
            season = "fall";
            break;
        }
        case 3:{
            season = "winter";
            break;
        }
      }
    weather = ui->weather->text().toStdString();
    location = ui->location->text().toStdString();
    temp = ui->temperature->text().toStdString();

    if(stoi(temp)<60){
        QMessageBox msgBox;
        msgBox.setText("Temperature must be greater than 60");
        msgBox.exec();
    }else{
    message = "For your configuration, the current temperature of ";
    message.append(location);
    message.append(" is ");
    message.append(temp);
    message.append(" and the current weather is ");
    message.append(weather);
    message.append(" your Hive Id is ");
    hiveId = cont.getQuery().query_max_hiveId()+1;
    message.append(to_string(hiveId));

    QMessageBox msgBox;
    msgBox.setText(QString::fromStdString(message));
    msgBox.exec();
    cont.add_hive(season, std::stoi(temp),location);

    UDPMessage* generator = new UDPMessage();
    std::chrono::system_clock::time_point t;
    t += std::chrono::milliseconds(1546300800000);

    std::string z;

    if (hiveId < 10) {
        z = "000";
        z.append(to_string(hiveId));
    }else if (hiveId < 100) {
        z = "00";
        z.append(to_string(hiveId));
    } else if (hiveId < 1000) {
        z = "0";
        z.append(to_string(hiveId));
    }

    generator->generate_random(56789, z, t, season, stoi(temp), state, 450);
    }
    }else{
        QString url = "https://api.darksky.net/forecast/d41b0d2b7b22391bbb7073731fb2a0e2/";
        url.append(ui->latitude->text());
        url.append(",");
        url.append(ui->longitude->text());

        req.setUrl(QUrl(url));
        qnam->get(req);
    }
}

void ConfigHive::fin(QNetworkReply *reply){

    string state;
    switch(ui->UserBox->currentIndex()){
    case 0: {
        state = "robbery";
        break;
    }
    case 1:{
        state = "swarm";
        break;
    }
    case 2:{
        state = "normal";
        break;
    }
    }

    QString qs = reply->readAll();
    std::string s = qs.toStdString();
    int curr = s.find("currently");
    int t = s.find("temperature", curr);
    int c = s.find("summary", curr);
    int l = s.find(",", c) - (c + 11);
    int h = s.find("humidity", curr);

    temp = s.substr(t + 13, 5);

    weather = s.substr(c + 10, l);
    location = ui->specific_location->text().toStdString();

    if(stoi(temp)<60){
        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString("current temperature is " + temp + " and it is too small. Temperatrue must be bigger than 60"));
        msgBox.exec();
    }else{
    message = "The current temperature of your location is ";
    message.append(temp);
    message.append(" and the current weather is ");
    message.append(weather);
    message.append(" your Hive Id is ");
    hiveId = cont.getQuery().query_max_hiveId()+1;
    message.append(to_string(hiveId));
    season = "winter";
    // Smaller multiple
        int j = (stoi(temp) / 10) * 10;

        // Larger multiple
        int b = j + 10;

        // Return of closest of two
        temp = to_string((stoi(temp) - j > b - stoi(temp))? b : j);

    cont.add_hive(season,std::stoi(temp),location);
    season = "spring";

    QMessageBox msgBox;
    msgBox.setText(QString::fromStdString(message));
    msgBox.exec();

    UDPMessage* generator = new UDPMessage();
    std::chrono::system_clock::time_point a;
    a += std::chrono::milliseconds(1546300800000);

    std::string z;

    if (hiveId < 10) {
        z = "000";
        z.append(to_string(hiveId));
    }else if (hiveId < 100) {
        z = "00";
        z.append(to_string(hiveId));
    } else if (hiveId < 1000) {
        z = "0";
        z.append(to_string(hiveId));
    }
    generator->generate_random(5125, z, a, season, stoi(temp), state, 450);
    }
}

ConfigHive::~ConfigHive()
{
    delete ui;
}

string ConfigHive::getSeason(){
    return season;
}

string ConfigHive::getWeather(){
    return weather;
}

string ConfigHive::getLocation(){
    return location;
}

