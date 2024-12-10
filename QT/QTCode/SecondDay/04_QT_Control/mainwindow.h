#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include <QRadioButton>
#include <QDebug>
#include <QGroupBox>
#include <QCheckBox>
#include <QListWidgetItem>
class mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    mainwindow(QWidget *parent = nullptr);
    ~mainwindow();

private:
    Ui::mainwindowClass ui;
};
