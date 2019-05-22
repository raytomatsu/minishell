#ifndef HIVEOWNER_H
#define HIVEOWNER_H

#include <QDialog>
#include "confighive.h"
#include "ui_confighive.h"
#include "updatehive.h"

#include "requestinfo.h"
#include "../ControlPackage/controller.h"
#include "requestinfoonehive.h"

namespace Ui {
class HiveOwner;
}

class HiveOwner : public QDialog
{
    Q_OBJECT

public:
    explicit HiveOwner(Controller cont,QWidget *parent = nullptr);
    ~HiveOwner();


private slots:
    void on_NewHive_Button_clicked();
    void on_UpdateHive_Button_clicked();

private:
    Ui::HiveOwner *ui;
    Controller cont;
};

#endif // HIVEOWNER_H
