#include "mainWidget.h"

mainWidget::mainWidget(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
}

mainWidget::~mainWidget()
{}

void mainWidget::paintEvent(QPaintEvent*)
{
    //实例化画家对象,this指定的是绘图设备
    QPainter painter(this);
    //设置画笔
    QPen pen(QColor(255,0,0));
    pen.setWidth(3);//宽度
    pen.setStyle(Qt::DotLine);//风格
    //使用画笔,红色
    painter.setPen(pen);

    //画刷，会填充封闭的图形
    QBrush brush(QColor(0,255,0));
    painter.setBrush(brush);
    //画线
    painter.drawLine(QPoint(0,0),QPoint(100,100));
    //画圆
    painter.drawEllipse(QPoint(100,100),50,50);
    //画矩形
    painter.drawRect(50,50,50,50);
    //画文字
    painter.drawText(QRect(10,200,150,50),"学习");

}
