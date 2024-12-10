#pragma once

#include <QtWidgets/QWidget>
#include "ui_mainWidget.h"
#include <QLabel>

class mainWidget : public QWidget
{
    Q_OBJECT

public:
    mainWidget(QWidget *parent = nullptr);
    ~mainWidget();

    //重写定时器事件
    void timerEvent(QTimerEvent *event);
     
    int id1;//定时器的id
    int id2;//定时器的id

private:
    Ui::mainWidgetClass ui;
};
