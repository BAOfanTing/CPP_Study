#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDialog>
#include <QMessageBox>
#include <QColorDialog>
#include <QFileDialog>
class mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    mainwindow(QWidget *parent = nullptr);
    ~mainwindow();

private:
    Ui::mainwindowClass ui;
};
