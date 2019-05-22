#ifndef CONFIGHIVE_H
#define CONFIGHIVE_H

#include <QDialog>
#include <QtNetwork>
#include <iostream>
#include <string>
#include <QMessageBox>

using namespace std;
namespace Ui {
class ConfigHive;
}

class ConfigHive : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigHive(QWidget *parent = nullptr);
    ~ConfigHive();
    string getWeather();
    string getSeason();
    string getLocation();

private slots:
    void on_ok_button_clicked();
    void fin(QNetworkReply *reply);

private:
    Ui::ConfigHive *ui;
    string weather;
    string season;
    string location;
    string temp;
    string message;
    QNetworkAccessManager *qnam = new QNetworkAccessManager(this);
    QNetworkRequest req;
};

#endif // CONFIGHIVE_H
