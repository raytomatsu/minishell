#ifndef UPDATEHIVE_H
#define UPDATEHIVE_H

#include <QDialog>
#include <string>

using namespace std;

namespace Ui {
class UpdateHive;
}

class UpdateHive : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateHive(QWidget *parent = nullptr);
    ~UpdateHive();

private slots:
    void on_pushButton_clicked();

private:
    Ui::UpdateHive *ui;
    string hiveId;

};

#endif // UPDATEHIVE_H
