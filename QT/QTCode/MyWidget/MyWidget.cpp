#include "MyWidget.h"
#include <QPushButton>
#include <QString>
#pragma execution_character_set("utf-8")
#include <QDebug>
MyWidget::MyWidget(QWidget *parent) 
    : QWidget(parent)
{
    ui.setupUi(this);

    //创建一个按钮
    QPushButton* btn1 = new QPushButton("first",this);
    //让按钮附加在窗口中
    btn1->setParent(this);


    QPushButton* btn2 = new QPushButton("我的按钮",this);
    //移动第二个按钮
    btn2->move(100,200);
    //重置窗口大小
    resize(600,400);

    //窗口固定大小无法拖拽
    setFixedSize(600,400);

    //设置窗口标题
    setWindowTitle("窗口");
    

    //需求点击我的按钮关闭框口
	//参数1 信号的发送者 参数2 发送的信号（函数的地址) 参数3 信号的接受者 参数4 处理的槽函数
    connect(btn2,&QPushButton::clicked,this,&MyWidget::close);
}

MyWidget::~MyWidget()
{}
