#pragma once

#include <QWidget>
#include "ui_smallWidget.h"
#include <QSpinBox>
#include <QSlider>
class smallWidget : public QWidget
{
	Q_OBJECT

public:
	smallWidget(QWidget *parent = nullptr);
	~smallWidget();
	//设置值
	void setNumber(int value);
	//得到值
	int getNumber();
	
private:
	Ui::smallWidgetClass ui;
};
