#pragma once

#include <QtWidgets/QWidget>
#include "ui_widget.h"
#include "Teacher.h"
#include "Student.h"
#include <QPushButton>
class widget : public QWidget
{
    Q_OBJECT

public:
    widget(QWidget *parent = nullptr);
    ~widget();

private:
    Ui::widgetClass ui;

    //先申明两个指针
    Teacher* te;
    Student* st;

    void classisover();
};
