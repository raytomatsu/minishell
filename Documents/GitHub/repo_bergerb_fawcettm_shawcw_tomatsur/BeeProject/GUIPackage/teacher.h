#ifndef TEACHER_H
#define TEACHER_H

#include <QDialog>
#include "requestinfo.h"
#include "ui_requestinfo.h"
#include "confighive.h"
#include "ui_confighive.h"

namespace Ui {
class Teacher;
}

class Teacher : public QDialog
{
    Q_OBJECT

public:
    explicit Teacher(QWidget *parent = nullptr);
    ~Teacher();

private:
    Ui::Teacher *ui;
};

#endif // TEACHER_H
