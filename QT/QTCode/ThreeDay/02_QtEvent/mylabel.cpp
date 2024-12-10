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

bool mylabel::event(QEvent* e)
{
	//如果是鼠标按下，在event事件分发中做拦截操作
	if (e->type() == QEvent::MouseButtonPress)
	{
		//类型转换，e是ev的父类
		QMouseEvent* ev = static_cast<QMouseEvent*>(e);
		QString str = QString("鼠标按下222 x =%1  y =%2 globalx=%3 ").arg(ev->pos().x()).arg(ev->pos().y()).arg(ev->globalPosition().toPoint().x());
		qDebug() << str;

		return true;//代表用户自己处理这个事件
	}
	//其他事件交给父类处理，默认处理
	return QLabel::event(e);
}
