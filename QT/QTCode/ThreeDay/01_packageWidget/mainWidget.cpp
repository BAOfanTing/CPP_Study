#include "mainWidget.h"

mainWidget::mainWidget(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    //点击获取值
    connect(ui.btn1,&QPushButton::clicked,[=](){
       qDebug()<< ui.widget->getNumber();
    });
    //点击设置值
	connect(ui.btn2, &QPushButton::clicked, [=]() {
        ui.widget->setNumber(50);
		qDebug() << ui.widget->getNumber();
	});
}

mainWidget::~mainWidget()
{}
