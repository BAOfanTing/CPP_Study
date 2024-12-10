#pragma once

#include <QtWidgets/QWidget>
#include "ui_mainWidget.h"
#include <QTableWidget>
#include <QStringList>

class mainWidget : public QWidget
{
    Q_OBJECT

public:
    mainWidget(QWidget *parent = nullptr);
    ~mainWidget();

private:
    Ui::mainWidgetClass ui;
};
