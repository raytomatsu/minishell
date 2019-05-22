#ifndef HIVEOWNER_H
#define HIVEOWNER_H

#include <QDialog>
#include "confighive.h"
#include "ui_confighive.h"
#include "updatehive.h"
#include "ui_updatehive.h"

namespace Ui {
class HiveOwner;
}

class HiveOwner : public QDialog
{
    Q_OBJECT

public:
    explicit HiveOwner(QWidget *parent = nullptr);
    ~HiveOwner();


private slots:
    void on_NewHive_Button_clicked();
    void on_UpdateHive_Button_clicked();

private:
    Ui::HiveOwner *ui;
};

#endif // HIVEOWNER_H
