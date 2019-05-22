#ifndef RESEARCHER_H
#define RESEARCHER_H

#include <QWidget>
#include "requestinfo.h"
#include "ui_requestinfo.h"
#include "confighive.h"
#include "ui_confighive.h"
#include "../ControlPackage/controller.h"
#include "requestgraph.h"

namespace Ui {
class Researcher;
}

class Researcher : public QWidget
{
    Q_OBJECT

public:
    explicit Researcher(Controller cont,QWidget *parent = nullptr);
    ~Researcher();

private slots:
    void on_requestInfo_Button_clicked();
    void on_configureNewHive_Button_clicked();

    void on_pushButton_clicked();

private:
    Ui::Researcher *ui;
    Controller cont;

};

#endif // RESEARCHER_H
