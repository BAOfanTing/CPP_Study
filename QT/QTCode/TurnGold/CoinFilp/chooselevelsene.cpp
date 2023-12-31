﻿#include "chooselevelsene.h"

chooselevelsene::chooselevelsene(QWidget *parent)
	: QMainWindow(parent)
{
	QSoundEffect* choosesound = new QSoundEffect(this);
	//加载本地文件
	choosesound->setSource(QUrl::fromLocalFile(":/res/TapButtonSound.wav"));

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

	connect(backBtn,&MyPushButton::clicked,[=](){
		qDebug()<<"点击返回";
		//播放音效
		QSoundEffect* backsound = new QSoundEffect(this);
		//加载本地文件
		backsound->setSource(QUrl::fromLocalFile(":/res/BackButtonSound.wav"));
		backsound->play();
		//告诉主场景返回了
		emit this->chooseSceneBack();
	});

	//生成一套矩阵的关卡图标
	for (int i = 0; i < 20; i++)
	{
		MyPushButton* menubtn = new MyPushButton(":/res/LevelIcon.png");
		menubtn->setParent(this);
		menubtn->move(25+i%4 * 70,130+i/4 * 70);

		//添加关卡文字组
		QLabel* label = new QLabel;
		label->setParent(this);
		label->setFixedSize(menubtn->width(),menubtn->height());
		label->setText(QString::number(i+1));
		label->move(25 + i % 4 * 70, 130 + i / 4 * 70);

		//设置label的字的对齐方式,居中
		label->setAlignment(Qt::AlignHCenter |Qt::AlignVCenter);
		//设置让鼠标穿透事件
		label->setAttribute(Qt::WA_TransparentForMouseEvents);


		//监听每个按钮的事件
		connect(menubtn,&MyPushButton::clicked,[=](){
			QString str = QString("您选择的是%1关").arg(i+1);
			qDebug() << str;

			//播放音效
			choosesound->play();

			//进入游戏场景
			this->hide();//隐藏选择关卡窗口
			play = new PlayScene(i+1);
			play->show();

			//设置游戏场景的初始位置
			play->setGeometry(this->geometry());

			//监听返回选择关卡的信号
			connect(play, &PlayScene::levelSceneBack, [=]() {
				qDebug() << "返回选择关卡111";
				//播放音效
				QSoundEffect* backsound = new QSoundEffect(this);
				//加载本地文件
				backsound->setSource(QUrl::fromLocalFile(":/res/BackButtonSound.wav"));
				backsound->play();
				QTimer::singleShot(500, this, [=]() {
					delete play;//删除当前关卡
					play = NULL;
					this->show();//显示选择关卡界面
					});

				this->setGeometry(play->geometry());
			});
		});
	}

	


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
