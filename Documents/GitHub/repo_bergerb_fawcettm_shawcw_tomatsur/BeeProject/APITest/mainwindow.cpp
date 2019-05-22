#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(qnam, &QNetworkAccessManager::finished, this, &MainWindow::fin);

    //first latitude

    req.setUrl(QUrl("https://api.darksky.net/forecast/d41b0d2b7b22391bbb7073731fb2a0e2/40.689350,-75.216698"));

    qnam->get(req);
}

void MainWindow::fin(QNetworkReply *reply){
    QString qs = reply->readAll();
    std::string s = qs.toStdString();
    int curr = s.find("currently");
    int t = s.find("temperature", curr);
    int c = s.find("summary", curr);
    int l = s.find(",", c) - (c + 11);
    int h = s.find("humidity", curr);

    std::string temp = s.substr(t + 13, 5);
    std::string cond = s.substr(c + 10, l);
    std::string humi = s.substr(h + 10, 4);
    ui->temp->setText(QString::fromStdString(temp));
    ui->cond->setText(QString::fromStdString(cond));
    ui->humi->setText(QString::fromStdString(humi));
}

MainWindow::~MainWindow()
{
    delete ui;
}
