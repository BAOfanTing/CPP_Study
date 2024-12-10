#pragma once

#include <QObject>
#include <QPushButton>
#include <QDebug>
#include <QPropertyAnimation>

class MyPushButton  : public QPushButton
{
	Q_OBJECT

public:
	MyPushButton(QWidget *parent);
	~MyPushButton();

	//构造函数参数1正常显示的图片路径―参数2按下后显示的图片路径
	MyPushButton(QString normaImg,QString pressImg = "");
	
	// 成员属性保存用户传入的默认显示路径以及按下后显示的图片路径
	QString normaImgPath;
	QString pressImgPath; 

	//弹跳特效
	void zoom1(bool isup = false);


	//重载鼠标按下和释放的事件
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);

};
