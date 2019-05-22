#include "graphsmulti.h"
#include "ui_graphsmulti.h"
#include <iostream>

GraphsMulti::GraphsMulti(vector<int> changeOne,vector<int> timeOne,vector<int> changeTwo, vector<int> timeTwo,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraphsMulti)
{
    ui->setupUi(this);

    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setPen(QPen(QColor(205,100,255)));
    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setPen(QPen(QColor(100,255,0)));

    QVector<double>x1(timeOne.size()),y1(changeOne.size());
    QVector<double>x2(timeOne.size()),y2(changeTwo.size());
    for (int i=0; i<timeOne.size(); i++)
    {
      x1[i] = timeOne.at(i); // x goes from -1 to 1
      y1[i] = changeOne.at(i); // let's plot a quadratic function
    }
    cout << endl;
    for(int i =0;i<timeOne.size();i++){
        x2[i] = timeOne.at(i);
        y2[i] = changeTwo.at(i);

    }
    // create graph and assign data to it:
    ui->customPlot->graph(0)->setData(x1, y1);
    ui->customPlot->graph(1)->setData(x1,y2);

    // give the axes some labels:
    ui->customPlot->xAxis->setLabelColor(Qt::white);
    ui->customPlot->xAxis->setLabel("Time");
    ui->customPlot->yAxis->setLabelColor(Qt::white);
    ui->customPlot->yAxis->setLabel("Net change Of Hive");

    ui->customPlot->graph(0)->rescaleAxes();
    ui->customPlot->graph(1)->rescaleAxes(true);


    // give the axes some labels:
    ui->customPlot->xAxis->setLabelColor(Qt::white);
    ui->customPlot->xAxis->setLabel("Time");
    ui->customPlot->yAxis->setLabelColor(Qt::white);
    ui->customPlot->yAxis->setLabel("Net change Of Hive");
    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->customPlot->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->customPlot->xAxis->setTickPen(QPen(Qt::white, 1));
    ui->customPlot->yAxis->setTickPen(QPen(Qt::white, 1));
    ui->customPlot->xAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->customPlot->yAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->customPlot->xAxis->setTickLabelColor(Qt::white);
    ui->customPlot->yAxis->setTickLabelColor(Qt::white);
    ui->customPlot->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->customPlot->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->customPlot->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->customPlot->xAxis->grid()->setSubGridVisible(true);
    ui->customPlot->yAxis->grid()->setSubGridVisible(true);
    ui->customPlot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customPlot->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customPlot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    ui->customPlot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);

    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    plotGradient.setColorAt(1, QColor(50, 50, 50));
    ui->customPlot->setBackground(plotGradient);
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(80, 80, 80));
    axisRectGradient.setColorAt(1, QColor(30, 30, 30));
    ui->customPlot->axisRect()->setBackground(axisRectGradient);

    ui->customPlot->rescaleAxes();

    long long maxTime = timeOne.at(timeOne.size()-1);
    ui->customPlot->yAxis->setRange(-50,50);
    ui->customPlot->xAxis->setRange(timeOne.at(0), maxTime);
    ui->customPlot->yAxis->setRange(-100,100);
    ui->customPlot->setInteraction(QCP::iRangeDrag, true);
    ui->customPlot->setInteraction(QCP::iRangeZoom, true);
    //ui->customPlot->replot();
}


GraphsMulti::~GraphsMulti()
{
    delete ui;
}
