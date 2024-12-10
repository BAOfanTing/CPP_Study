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
#include "dataconfig.h"

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

	//二维数组维护每关的具体数据
	int gameArry[4][4];

signals:
	//写一个自定义信号，告诉选择场景，点击了返回
	void levelSceneBack();
};
