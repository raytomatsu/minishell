#ifndef GRAPHSTWO_H
#define GRAPHSTWO_H

#include <QDialog>
#include <vector>

using namespace std;

namespace Ui {
class graphsTwo;
}

class graphsTwo : public QDialog
{
    Q_OBJECT

public:
    explicit graphsTwo(vector<int> timeOne,vector<int>changeOne,vector<int>timeTwo, vector<int> changeTwo,QWidget *parent = nullptr);
    ~graphsTwo();

private:
    Ui::graphsTwo *ui;
};

#endif // GRAPHSTWO_H
