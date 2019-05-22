#ifndef REQUESTINFO_H
#define REQUESTINFO_H

#include <string>
#include <QDialog>

using namespace std;

namespace Ui {
class RequestInfo;
}

class RequestInfo : public QDialog
{
    Q_OBJECT

public:
    explicit RequestInfo(QWidget *parent = nullptr);
    ~RequestInfo();
    string getSeason();
    string getHiveId();
    string getWeather();
    string getLocation();

private slots:
    void on_ok_button_clicked();
    void on_hiveID_pushButton_clicked();

private:
    Ui::RequestInfo *ui;
    string season;
    string hiveId;
    string weather;
    string location;
    string temp;
};

#endif // REQUESTINFO_H
