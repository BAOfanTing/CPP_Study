#include "mylabel.h"

mylabel::mylabel(QWidget*parent)
	: QLabel(parent)
{
	//设置鼠标追踪，默认false
	setMouseTracking(true);
}

mylabel::~mylabel()
{}

void mylabel::enterEvent(QEnterEvent * event)
{
	qDebug() <<"鼠标进入了";
}

void mylabel::leaveEvent(QEvent* event)
{
	qDebug() << "鼠标离开了";
}

void mylabel::mousePressEvent(QMouseEvent* ev)
{
	//QT6很多都删了但是还能使用，不推荐
	/*if(ev->button() == Qt::LeftButton)
	{*/
		QString str = QString("鼠标按下 x =%1  y =%2 globalx=%3 ").arg(ev->pos().x()).arg(ev->pos().y()).arg(ev->globalPosition().toPoint().x());
		qDebug() << str;
	/*}*/
}

void mylabel::mouseReleaseEvent(QMouseEvent* ev)
{
	/*if (ev->button() == Qt::LeftButton)
	{*/
		qDebug() << "鼠标释放";
	/*}*/
}

void mylabel::mouseMoveEvent(QMouseEvent* ev)
{
	//因为移动是个过程，所以直接==不能够触发，这边用的是buttons，里边包含了三种状态，使用与操作符，当状态和Leftbutton相同时触发
	/*if (ev->button() & Qt::LeftButton)
	{*/
		qDebug() << "鼠标移动111";
	/*}*/
}
