#ifndef GRAPHSMULTI_H
#define GRAPHSMULTI_H

#include <QDialog>
#include <vector>

using namespace std;

namespace Ui {
class GraphsMulti;
}

class GraphsMulti : public QDialog
{
    Q_OBJECT

public:
    explicit GraphsMulti(vector<int> changeOne,vector<int> timeOne,vector<int> changeTwo, vector<int> timeTwo,QWidget *parent = nullptr);
    ~GraphsMulti();
    int smallest();
    int biggest();

private:
    Ui::GraphsMulti *ui;
};

#endif // GRAPHSMULTI_H
