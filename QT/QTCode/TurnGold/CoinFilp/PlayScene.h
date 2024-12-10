#pragma once

#include <QMainWindow>
#include <QDebug>
#include <QMenuBar>
#include <QMenu>
#include <QPainter>
#include <QPixmap>
#include "MyPushButton.h"
#include <QLabel>
#include "MyCoin.h"
class PlayScene  : public QMainWindow
{
	Q_OBJECT

public:
	/*PlayScene(QObject *parent);*/
	~PlayScene();

	//重写构造
	PlayScene(int level);

	int levelindex ;
	//重写绘图事件添加背景
	void paintEvent(QPaintEvent *event);

signals:
	//写一个自定义信号，告诉选择场景，点击了返回
	void levelSceneBack();
};
