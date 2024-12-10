#include "mainWidget.h"

mainWidget::mainWidget(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    //栈控件的使用
	//设置第一个界面
	ui.stackedWidget->setCurrentIndex(1);

    //toolbox按钮的使用
	connect(ui.toolboxbtn, &QPushButton::clicked, [=]() {
		ui.stackedWidget->setCurrentIndex(0);
	});

	connect(ui.tabbtn, &QPushButton::clicked, [=]() {
		ui.stackedWidget->setCurrentIndex(1);
	});

	//下拉框
	ui.comboBox->addItem("奔驰");
	ui.comboBox->addItem("宝马");
	ui.comboBox->addItem("拖拉机");
	//按按钮选中拖拉机
	connect(ui.comboBoxbtn,&QPushButton::clicked,[=](){
		ui.comboBox->setCurrentIndex(2);
	});
	
	//Qlable显示图片，还能显示动图
	ui.label1->setPixmap(QPixmap(":/Image/butterfly.png"));

	QMovie* movie = new QMovie(":/Image/mario.gif");
	ui.label2->setMovie(movie);
	//播放动图
	movie->start();
}

mainWidget::~mainWidget()
{}
