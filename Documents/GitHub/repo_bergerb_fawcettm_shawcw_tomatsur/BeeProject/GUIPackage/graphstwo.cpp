#include "graphstwo.h"
#include "ui_graphstwo.h"

graphsTwo::graphsTwo(vector<int> timeOne,vector<int>changeOne,vector<int>timeTwo, vector<int> changeTwo,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::graphsTwo)
{
    ui->setupUi(this);

}

graphsTwo::~graphsTwo()
{
    delete ui;
}
