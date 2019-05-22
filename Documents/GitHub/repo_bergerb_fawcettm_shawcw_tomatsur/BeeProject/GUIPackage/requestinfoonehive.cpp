#include "requestinfoonehive.h"
#include "ui_requestinfoonehive.h"

RequestInfoOneHive::RequestInfoOneHive(Controller cont,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RequestInfoOneHive)
{
    ui->setupUi(this);
    this->cont=cont;
}

RequestInfoOneHive::~RequestInfoOneHive()
{
    delete ui;
}

void RequestInfoOneHive::on_pushButton_clicked()
{
    if(ui->hiveId->text().toStdString().empty()){
        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString("Please Input all Necessary Parameters!"));
        msgBox.exec();
    }else{
        if(stoi(ui->hiveId->text().toStdString())>cont.maxId()){
            QMessageBox msgBox;
            msgBox.setText(QString::fromStdString("Hive ID does not exist!"));
            msgBox.exec();
        }else{
        DisplayInfo *dI = new DisplayInfo(stoi(ui->hiveId->text().toStdString()),cont);
        dI->show();
        }
    }
}
