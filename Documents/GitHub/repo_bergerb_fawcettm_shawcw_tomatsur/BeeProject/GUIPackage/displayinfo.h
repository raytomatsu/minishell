#ifndef DISPLAYINFO_H
#define DISPLAYINFO_H

#include <QDialog>
#include "../ControlPackage/controller.h"
#include "graph.h"
#include <QTimer>
#include <vector>

namespace Ui {
class DisplayInfo;
}

class DisplayInfo : public QDialog
{
    Q_OBJECT

public:
    explicit DisplayInfo(int,Controller cont,QWidget *parent = nullptr);
    ~DisplayInfo();
    void startSimulation();
    vector<long long> extract_times();
    void updateEntry(int);
    void updateExit(int);
    void updateTime(int, int, int);
    void updatePeak(int);
    void checkWarning();
    void displayChart();
    void userSpeed();
    tm* translateTime(long long time);

public slots:
    void updateLabel();

private slots:
    void on_pushButton_clicked();

private:
    Ui::DisplayInfo *ui;
    int hiveId;
    double sf;
    Controller cont;
    std::vector<Event*> events;
    QTimer* timer;
    int entries;
    int exits;
    int peak;
    int index;
    int netChange;
    string season;
    int temp;
    vector<int> netChangeArray;
    vector<int> time;

};

#endif // DISPLAYINFO_H
