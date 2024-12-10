#pragma once

#include <QObject>
#include <QEnterEvent>
#include <QEvent>
#include <QDebug>
#include <QLabel>
#include <QMouseEvent>

class mylabel  : public QLabel
{
	Q_OBJECT

public:
	mylabel(QWidget* parent);
	~mylabel();
	//鼠标进入
	void enterEvent(QEnterEvent* event);
	//鼠标离开
	void leaveEvent(QEvent* event);
	//鼠标按下
	void mousePressEvent(QMouseEvent* ev);
	//鼠标释放
	void mouseReleaseEvent(QMouseEvent* ev);
	//鼠标移动
	void mouseMoveEvent(QMouseEvent* ev);

	//通过Event事件分发器拦截鼠标按下事件
	bool event(QEvent *e);
};
