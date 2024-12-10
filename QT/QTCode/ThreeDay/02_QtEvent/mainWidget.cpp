#include "mainWidget.h"
#include <QTimer>
mainWidget::mainWidget(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    //启动定时器
    id1 = startTimer(1000);//单位毫秒，每隔一秒调用函数

    id2 = startTimer(2000);//单位毫秒，每隔2秒调用函数

	//定时器的第二种方式
	QTimer* timer = new QTimer(this);
	//启动定时器
	timer->start(500);

	connect(timer,&QTimer::timeout,[=](){
		static int num2 = 1;
		ui.label3->setText(QString::number(num2++));
	});
	//点击按钮暂停
	connect(ui.btn1,&QPushButton::clicked,[=](){
		timer->stop();
	});

	//给label1安装事件过滤器
	//1、安装事件过滤器
	ui.label1->installEventFilter(this);
	//2、重写事件
}

//2、重写事件,obj就是控件
bool mainWidget::eventFilter(QObject* watched, QEvent* event)
{
	if (watched == ui.label1)
	{
		if (event->type() == QEvent::MouseButtonPress)
		{
			//类型转换，e是ev的父类
			QMouseEvent* ev = static_cast<QMouseEvent*>(event);
			QString str = QString("事件过滤器鼠标按下 x =%1  y =%2 globalx=%3 ").arg(ev->pos().x()).arg(ev->pos().y()).arg(ev->globalPosition().toPoint().x());
			qDebug() << str;
		}
	}
	//默认交给父类处理
	return QWidget::eventFilter(watched,event);
}


mainWidget::~mainWidget()
{}

void mainWidget::timerEvent(QTimerEvent * event)
{

	if (event->timerId() == id1)
	{
		static int num = 1;
		ui.label2->setText(QString::number(num++));
	}
 //   //两秒跳一次
	//if (event->timerId() == id2)
	//{
	//	static int num2 = 1;
	//	ui.label3->setText(QString::number(num2++));
	//}
    
}
