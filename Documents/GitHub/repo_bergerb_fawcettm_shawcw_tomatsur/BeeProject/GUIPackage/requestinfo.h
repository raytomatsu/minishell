#ifndef REQUESTINFO_H
#define REQUESTINFO_H

#include <string>
#include <QDialog>
#include "../ControlPackage/controller.h"
#include <QMessageBox>
#include "displayinfo.h"

using namespace std;

namespace Ui {
class RequestInfo;
}

class RequestInfo : public QDialog
{
    Q_OBJECT

public:
    explicit RequestInfo(Controller cont,QWidget *parent = nullptr);
    ~RequestInfo();
    string getSeason();
    int getHiveId();
    string getWeather();
    string getLocation();
    bool checkInfo();
    void Qmsg();

private slots:
    void on_ok_button_clicked();
    void on_hiveID_pushButton_clicked();

private:
    Ui::RequestInfo *ui;
    string season;
    int hiveId;
    string weather;
    string location;
    string temp;
    Controller cont;
};

#endif // REQUESTINFO_H
