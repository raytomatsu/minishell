#ifndef REQUESTINFOONEHIVE_H
#define REQUESTINFOONEHIVE_H

#include <QDialog>
#include "../ControlPackage/controller.h"
#include <QMessageBox>
#include "displayinfo.h"

namespace Ui {
class RequestInfoOneHive;
}

class RequestInfoOneHive : public QDialog
{
    Q_OBJECT

public:
    explicit RequestInfoOneHive(Controller cont,QWidget *parent = nullptr);
    ~RequestInfoOneHive();

private slots:
    void on_pushButton_clicked();

private:
    Ui::RequestInfoOneHive *ui;
    Controller cont;
};

#endif // REQUESTINFOONEHIVE_H
