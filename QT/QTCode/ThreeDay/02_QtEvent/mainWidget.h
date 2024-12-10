#pragma once

#include <QtWidgets/QWidget>
#include "ui_mainWidget.h"

class mainWidget : public QWidget
{
    Q_OBJECT

public:
    mainWidget(QWidget *parent = nullptr);
    ~mainWidget();

private:
    Ui::mainWidgetClass ui;
};
