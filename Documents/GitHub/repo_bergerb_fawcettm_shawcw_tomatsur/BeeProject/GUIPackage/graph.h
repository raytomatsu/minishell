#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>
#include <vector>
#include <string>

using namespace std;

namespace Ui {
class Graph;
}

class Graph : public QDialog
{
    Q_OBJECT

public:
    explicit Graph(vector<int>,vector<int>,QWidget *parent = nullptr);
    ~Graph();
    int largest();
    int smallest();
    void makeGraph();

private slots:
    void on_zoom_clicked();

private:
    Ui::Graph *ui;
    vector<int> change;
    vector<int> time;

};

#endif // GRAPH_H
