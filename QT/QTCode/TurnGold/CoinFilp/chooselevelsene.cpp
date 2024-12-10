#include "chooselevelsene.h"

chooselevelsene::chooselevelsene(QWidget *parent)
	: QMainWindow(parent)
{
	//设置固定大小
	this->setFixedSize(320, 580);
	//设置图片
	this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
	//设置框口标题
	this->setWindowTitle("选择场景");

	//创建菜单栏
	QMenuBar* bar= menuBar();
	setMenuBar(bar);

	//创建开始菜单
	QMenu* startMenu = bar->addMenu("开始");

	//创建退出
	QAction* quitAction = startMenu->addAction("退出");

	startMenu->addAction(quitAction);
	connect(quitAction,&QAction::triggered,[=](){
		this->close();
	});
	//返回按钮
	MyPushButton* backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
	backBtn->setParent(this);
	backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

	connect(backBtn,&QPushButton::pressed,[=](){
		qDebug()<<"点击返回";
		//告诉主场景返回了
		emit this->chooseSceneBack();
	});
}

chooselevelsene::~chooselevelsene()
{}

void chooselevelsene::paintEvent(QPaintEvent*)
{
	
	//创建画家
	QPainter painter(this);
	//加载图片
	QPixmap pix;
	pix.load(QString(":/res/OtherSceneBg.png"));

	//绘制背景
	painter.drawPixmap(0, 0, this->width(), this->height(), pix);


	//加载标题
	pix.load(":/res/Title.png");
	//绘制标题
	painter.drawPixmap((this->width()-pix.width()) * 0.5, 30, pix.width(), pix.height(), pix);
}
