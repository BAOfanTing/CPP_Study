#pragma once

#include <QObject>
#include <QPushButton>
#include <QTimer>

class MyCoin  : public QPushButton
{
	Q_OBJECT

public:
	/*MyCoin(QWidget *parent);*/
	~MyCoin();
	//显示的是金币还是银币
	MyCoin(QString btnImg);

	int posX;//x坐标位置
	int posY;//y坐标位置
	bool flag;//正反标志


	//改变标志的方法
	void changeFlag();
	QTimer *timer1;
	QTimer *timer2;

	int min =1;
	int max = 8;

	//执行动画的标准
	bool isAnimation = false;

	//重写按下事件
	void mousePressEvent(QMouseEvent *e);

	//胜利后不能点击
	bool Canclick = true;
};
