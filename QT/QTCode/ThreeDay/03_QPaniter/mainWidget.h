#pragma once

#include <QtWidgets/QWidget>
#include "ui_mainWidget.h"
#include <QPaintEvent>
#include <QPainter>
#include <QPoint>
#include <QPushButton>

class mainWidget : public QWidget
{
    Q_OBJECT

public:
    mainWidget(QWidget *parent = nullptr);
    ~mainWidget();

    //��ͼ�¼�
    void paintEvent(QPaintEvent *);

    int pos = 0;
private:
    Ui::mainWidgetClass ui;
};
