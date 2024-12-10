#pragma once

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QPainter>
#include "MyPushButton.h"
#include <QLabel>
#include "PlayScene.h"
#include <QTimer>

class chooselevelsene  : public QMainWindow
{
	Q_OBJECT

public:
	chooselevelsene(QWidget *parent);
	~chooselevelsene();

	//重写绘图事件，画背景图
	void paintEvent(QPaintEvent*);

	//创建游戏场景指针
	PlayScene* play = NULL;

signals:
	//写一个自定义信号，告诉主场景，点击了返回
	void chooseSceneBack();

};
