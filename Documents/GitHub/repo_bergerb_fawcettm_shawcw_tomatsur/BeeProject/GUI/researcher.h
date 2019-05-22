#ifndef RESEARCHER_H
#define RESEARCHER_H

#include <QWidget>
#include "requestinfo.h"
#include "ui_requestinfo.h"
#include "confighive.h"
#include "ui_confighive.h"

namespace Ui {
class Researcher;
}

class Researcher : public QWidget
{
    Q_OBJECT

public:
    explicit Researcher(QWidget *parent = nullptr);
    ~Researcher();

private slots:
    void on_requestInfo_Button_clicked();
    void on_configureNewHive_Button_clicked();

private:
    Ui::Researcher *ui;

};

#endif // RESEARCHER_H
