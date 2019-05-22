#include "confighive.h"
#include "ui_confighive.h"

ConfigHive::ConfigHive(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigHive)
{
    ui->setupUi(this);
    QObject::connect(qnam, &QNetworkAccessManager::finished, this, &ConfigHive::fin);

}

void ConfigHive::on_ok_button_clicked()
{
    //manual input of parameteres
    if(ui->longitude->text().toStdString().empty()){
    season = ui->season->text().toStdString();
    weather = ui->weather->text().toStdString();
    location = ui->location->text().toStdString();
    temp = ui->temperature->text().toStdString();

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

    message = "The current temperature of your location is ";
    message.append(temp);
    message.append(" and the current weather is ");
    message.append(weather);

    QMessageBox msgBox;
    msgBox.setText(QString::fromStdString(message));
    msgBox.exec();
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

