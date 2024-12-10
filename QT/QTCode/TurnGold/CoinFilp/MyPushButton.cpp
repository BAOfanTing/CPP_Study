#include "MyPushButton.h"

MyPushButton::MyPushButton(QWidget *parent)
	: QPushButton(parent)
{}

MyPushButton::~MyPushButton()
{}

MyPushButton::MyPushButton(QString normaImg, QString pressImg)
{
	this->normaImgPath = normaImg;
	this->pressImgPath = pressImg;

	QPixmap pix;
	bool ret = pix.load(normaImg);
	if (!ret)
	{
		qDebug() << "图片加载失败！";
		return ;
	}

	//设置图片固定大小
	this->setFixedSize(pix.width(),pix.height());
	//设置不规则图片样式,不设置就是正方向按钮设置了就是
	this->setStyleSheet("QPushButton{border:0px;}");
	//设置图标
	this->setIcon(pix);
	//设置图标大小
	this->setIconSize(QSize(pix.width(),pix.height()));
}

void MyPushButton::zoom1(bool isup)
{
	//创建动态特效
	QPropertyAnimation* animation = new QPropertyAnimation(this,"geometry");
	//设置时间间隔
	animation->setDuration(200);
	if (isup)
	{
		//起始位置
		animation->setStartValue(QRect(this->x(), this->y() + 10 , this->width(), this->height()));
		//结束位置
		animation->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));
	}
	else
	{
		//起始位置
		animation->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
		//结束位置
		animation->setEndValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));
	}
	
	
	//设置弹跳曲线
	animation->setEasingCurve(QEasingCurve::OutBounce);
	//执行动画
	animation->start();
}

void MyPushButton::mousePressEvent(QMouseEvent* e)
{
	if (this->pressImgPath != "")//传入图片不为空，切换图片
	{
		QPixmap pix;
		bool ret = pix.load(pressImgPath);
		if (!ret)
		{
			qDebug() << "图片加载失败！";
			return;
		}
		this->setFixedSize(pix.width(),pix.height());
		//设置不规则图片样式,不设置就是正方向按钮设置了就是
		this->setStyleSheet("QPushButton{border:0px;}");
		//设置按钮的图标
		this->setIcon(pix);
		//设置按钮图标大小
		this->setIconSize(QSize(pix.width(), pix.height()));
	}

	//重载事件后让它继续执行父类的东西
	return QPushButton::mousePressEvent(e);

}

void MyPushButton::mouseReleaseEvent(QMouseEvent* e)
{
	if (this->pressImgPath != "")//传入图片不为空，切换图片
	{
		QPixmap pix;
		bool ret = pix.load(normaImgPath);
		if (!ret)
		{
			qDebug() << "图片加载失败！";
			return;
		}
		this->setFixedSize(pix.width(), pix.height());
		//设置不规则图片样式,不设置就是正方向按钮设置了就是
		this->setStyleSheet("QPushButton{border:0px;}");
		//设置图标
		this->setIcon(pix);
		//设置图标大小
		this->setIconSize(QSize(pix.width(), pix.height()));
	}

	//重载事件后让它继续执行父类的东西
	return QPushButton::mouseReleaseEvent(e);

}


