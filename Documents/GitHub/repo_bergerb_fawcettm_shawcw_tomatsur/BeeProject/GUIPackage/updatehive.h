#ifndef UPDATEHIVE_H
#define UPDATEHIVE_H

#include <QDialog>
#include <string>
#include "../ControlPackage/controller.h"

using namespace std;

namespace Ui {
class UpdateHive;
}

class UpdateHive : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateHive(Controller cont,QWidget *parent = nullptr);
    ~UpdateHive();

private slots:
    void on_pushButton_clicked();

private:
    Ui::UpdateHive *ui;
    string hiveId;
    Controller cont;

};

#endif // UPDATEHIVE_H
