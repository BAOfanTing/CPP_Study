#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainWidget.h"
#include <QPushButton.h>
#include <QFileDialog.h>
#include <QFileInfo.h>
#include <qdebug.h>
class mainWidget : public QMainWindow
{
    Q_OBJECT

public:
    mainWidget(QWidget *parent = nullptr);
    ~mainWidget();

private:
    Ui::mainWidgetClass ui;
};
