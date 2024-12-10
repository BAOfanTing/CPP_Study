#pragma once

#include <QtWidgets/QWidget>
#include "ui_mainWidget.h"
#include <QPushButton>
#include <QLabel>
#include <QMovie>
#include <QPixmap>
class mainWidget : public QWidget
{
    Q_OBJECT

public:
    mainWidget(QWidget *parent = nullptr);
    ~mainWidget();

private:
    Ui::mainWidgetClass ui;
};
