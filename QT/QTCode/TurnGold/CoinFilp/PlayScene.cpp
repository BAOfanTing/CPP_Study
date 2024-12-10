#include "PlayScene.h"

//PlayScene::PlayScene(QObject *parent)
//	: QMainWindow(parent)
//{}

PlayScene::~PlayScene()
{}

PlayScene::PlayScene(int level)
{
	QString str = QString("第%关").arg(level);
	qDebug() << str;
	this->levelindex = level;

	//初始化游戏场景
	this->setFixedSize(320,580);
	//设置图标
	this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
	//设置标题
	this->setWindowTitle(str);

	//创建菜单栏
	QMenuBar* bar = menuBar();
	setMenuBar(bar);

	//创建菜单栏
	QMenu* startMenu = bar->addMenu("开始");
	//创建退出菜单项
	QAction* quitAction = startMenu->addAction("退出");
	//退出游戏
	connect(quitAction,&QAction::triggered,[=](){
		this->close();
	
	});


	//返回按钮
	MyPushButton* backBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
	backBtn->setParent(this);
	backBtn->move(this->width() - backBtn->width(), this->height() - backBtn->height());

	connect(backBtn, &MyPushButton::clicked, [=]() {
		qDebug() << "返回选择关卡";
		//告诉选择关卡返回了
		emit this->levelSceneBack();
	});
}

void PlayScene::paintEvent(QPaintEvent* event)
{
	//创建画家
	QPainter painter(this);
	//加载图片
	QPixmap pix;
	pix.load(":/res/OtherSceneBg.png");

	//绘制背景
	painter.drawPixmap(0,0,pix.width(),pix.height(),pix);

	//加载标题
	pix.load(":/res/Title.png");
	//绘制标题
	painter.drawPixmap((this->width() - pix.width()) * 0.5, 30, pix.width(), pix.height(), pix);

}
