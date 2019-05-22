#ifndef REQUESTGRAPH_H
#define REQUESTGRAPH_H

#include <QDialog>
#include "../ControlPackage/Controller.h"
#include <QMessageBox>
#include "graphobj.h"
#include <vector>
#include "graphsmulti.h"

using namespace std;

namespace Ui {
class RequestGraph;
}

class RequestGraph : public QDialog
{
    Q_OBJECT

public:
    explicit RequestGraph(Controller,QWidget *parent = nullptr);
    ~RequestGraph();

    void generate(vector<Event*>);
    void generate2(vector<Event*>);
    bool checkInfo();

private slots:
    void on_ok_button_clicked();

private:
    Ui::RequestGraph *ui;
    Controller cont;
    std::vector<Event*> events1;
    std::vector<Event*> events2;
    vector<int> changeOne;
    vector<int> timeOne;
    vector<int> changeTwo;
    vector<int> timeTwo;
};

#endif // REQUESTGRAPH_H
