#include "graph.h"
#include "ui_graph.h"

Graph::Graph(vector<int> time,vector<int> change,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Graph)
{
    ui->setupUi(this);
    this->time = time;
    this->change = change;
    makeGraph();

}

void Graph::makeGraph(){
    QVector<double>x(time.size()),y(change.size());
    for (int i=0; i<time.size(); ++i)
    {
      x[i] = time.at(i);
      y[i] = change.at(i);
    }
    // create graph and assign data to it:
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x, y);


    //dots in graph 1 line in graph 2
    QCPGraph *graph1 = ui->customPlot->addGraph();
    graph1->setData(x, y);
    //graph1->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1.5), QBrush(Qt::white), 9));
    graph1->setPen(QPen(QColor(250, 120, 120), 2));

    QCPGraph *graph2 = ui->customPlot->addGraph();
    graph2->setData(x, y);
    graph2->setPen(Qt::NoPen);
    graph2->setBrush(QColor(200, 200, 200, 20));
    graph2->setChannelFillGraph(graph1);

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

    //set ranges from smallest to largest of each pieces of data.

    long long maxTime = time.at(time.size()-1);
    ui->customPlot->xAxis->setRange(time.at(0), maxTime);
    ui->customPlot->yAxis->setRange(smallest(), largest());

    ui->customPlot->setInteraction(QCP::iRangeDrag, true);
    ui->customPlot->setInteraction(QCP::iRangeZoom, true);
    ui->customPlot->replot();
}


//searches for the largest point, sets the range
int Graph::largest(){
    int biggest = change.at(0);
    for(int i =0; i<change.size();i++){
        if(change.at(i)>biggest){
            biggest = change.at(i);
        }
    }
    return biggest;
}

//searches for the smallest point, sets the range
int Graph::smallest(){
    int smallest = change.at(0);
    for(int i =0; i<change.size();i++){
        if(change.at(i)<smallest){
            smallest = change.at(i);
        }
    }
    return smallest;
}

Graph::~Graph()
{
    delete ui;
}

void Graph::on_zoom_clicked()
{

}
