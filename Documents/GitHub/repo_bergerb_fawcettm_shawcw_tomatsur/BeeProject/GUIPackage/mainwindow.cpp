#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //controller for the CONTROLPACKAGE
    cont = new Controller();

    //welcome page

    QMessageBox init;
    init.setText("Ray Tomatsu, Carson Shaw, Brett Berger, Molly Fawcett\n "
                 "We focused on User types Hive Owner, Teacher, and Researcher\n"
                 "Our data is able to be generated using multiple parameters and interprets through math models to create alerts through various special events\n"
                 "          Welcome to the Bee++ Hive Manager for Circle of Bees, who's hives collect real-time data on the bee activity through out"
                 "the day. If you are a hive owner, this program will allow you to watch a simulation of your hive activity and whether or"
                 "not a swarm or robbery is likely. If you are a teacher or a researcher, this program allows access to see previous hive's "
                 "data such that you can analyze one or more hives' activity on a given day through our graphing functionality. Simply identify"
                 "what kind of user you are, and the program will work best for your needs.");
    init.exec();
    QMessageBox ref;
    ref.setText("References "
                "https://www.google.com/url?sa=i&rct=j&q=&esrc=s&source=images&cd=&cad=rja&uact=8&ved=2ahUKEwiRt6vJgI3iAhVhx1kKHVn-DjQQjRx6BAgBEAU&url=https%3A%2F%2Fwww.vectorstock.com%2Froyalty-free-vector%2Fdaisy-flower-with-bee-background-vector-20685265&psig=AOvVaw20SZ-AV3_qVF-cc0ZMlO_0&ust=1557441694056417"
                "https://www.google.com/url?sa=i&rct=j&q=&esrc=s&source=images&cd=&cad=rja&uact=8&ved=2ahUKEwiznI-A_4ziAhWBxFkKHY10CQ0QjRx6BAgBEAU&url=https%3A%2F%2Fpngtree.com%2Ffreebackground%2Fcute-bee-yellow-background_120077.html&psig=AOvVaw0CZce61HMawwLE2syCgKUT&ust=1557441270118249");
    QFont f("Times",9);
    ref.setFont(f);
    ref.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Exit_Button_clicked()
{
    close();
}


//choosing the user
void MainWindow::on_Ok_Button_clicked()
{
    //index of the user box cooresponds to these users
    switch(ui->UserBox->currentIndex()){
    case 0: {
        Researcher* r = new Researcher(*cont);
        //researcher page
        r->show();
        break;
    }
    case 1:{
        RequestInfo *rI = new RequestInfo(*cont);
        //teacher
        rI->show();
        break;
    }
    case 2:{
        HiveOwner* hO = new HiveOwner(*cont);
        //hiveowner page
        hO->show();
        break;
    }
  }
}
