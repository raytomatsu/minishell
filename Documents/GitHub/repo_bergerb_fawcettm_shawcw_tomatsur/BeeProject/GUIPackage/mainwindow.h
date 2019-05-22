#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFont>

#include "hiveowner.h"
#include "ui_hiveowner.h"
#include "researcher.h"
#include "ui_researcher.h"
#include "requestinfo.h"
#include "ui_requestinfo.h"
#include "../ControlPackage/controller.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Exit_Button_clicked();
    void on_Ok_Button_clicked();



private:
    Ui::MainWindow *ui;
    Controller *cont;

};

#endif // MAINWINDOW_H
