#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Exit_Button_clicked()
{
    close();
}

void MainWindow::on_Ok_Button_clicked()
{
    switch(ui->UserBox->currentIndex()){
    case 0: {
        Researcher* r = new Researcher();
        r->show();
        break;
    }
    case 1:{
        RequestInfo *rI = new RequestInfo();
        rI->show();
        break;
    }
    case 2:{
        HiveOwner* hO = new HiveOwner();
        hO->show();
        break;
    }
  }
}
