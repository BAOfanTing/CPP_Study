#include "mainWidget.h"

mainWidget::mainWidget(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    //点击按钮移动图片
	connect(ui.btn1, &QPushButton::clicked, [=]() {
    //如果要手动调用绘图事件使用update
        pos += 20;
        update();
	});
}

mainWidget::~mainWidget()
{}

void mainWidget::paintEvent(QPaintEvent*)
{
    ////实例化画家对象,this指定的是绘图设备
    //QPainter painter(this);
    ////设置画笔
    //QPen pen(QColor(255,0,0));
    //pen.setWidth(3);//宽度
    //pen.setStyle(Qt::DotLine);//风格
    ////使用画笔,红色
    //painter.setPen(pen);

    ////画刷，会填充封闭的图形
    //QBrush brush(QColor(0,255,0));
    //painter.setBrush(brush);
    ////画线
    //painter.drawLine(QPoint(0,0),QPoint(100,100));
    ////画圆
    //painter.drawEllipse(QPoint(100,100),50,50);
    ////画矩形
    //painter.drawRect(50,50,50,50);
    ////画文字
    //painter.drawText(QRect(10,200,150,50),"学习");


    ////////////////////////高级绘图/////////////////////////
    //指定当前窗口绘图
    /*QPainter painter(this);*/
	////画圆
	//painter.drawEllipse(QPoint(100,100),50,50);
 //   //设置抗锯齿
 //   painter.setRenderHint(QPainter::Antialiasing);
 //   painter.drawEllipse(QPoint(200, 200), 50, 50);

    ////画矩形
    //painter.drawRect(QRect(20,20,50,50));

    ////移动画家,水平移动，绘画的初始点移动
    //painter.translate(100,0);
    ////相当于保存这个移动后的点
    //painter.save();
    //painter.drawRect(QRect(20, 20, 50, 50));

    //painter.translate(100, 0);
    ////复原状态，相当于退回到保存点
    //painter.restore();
    //painter.drawRect(QRect(20, 20, 50, 50));



    ////////////////////////画资源图片/////////////////////////
	//指定当前窗口绘图
	QPainter painter(this);

    if (pos>this->width())
    {
        pos = 0; 
    }
    painter.drawPixmap(pos,0,QPixmap(":/Image/butterfly.png"));

    
}
