#pragma once

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QPainter>
#include "MyPushButton.h"
#include <QLabel>

class chooselevelsene  : public QMainWindow
{
	Q_OBJECT

public:
	chooselevelsene(QWidget *parent);
	~chooselevelsene();

	//重写绘图事件，画背景图
	void paintEvent(QPaintEvent*);

signals:
	//写一个自定义信号，告诉主场景，点击了返回
	void chooseSceneBack();

};
