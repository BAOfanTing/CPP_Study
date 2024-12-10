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
	
	//显示当前关卡
	QLabel* label =new QLabel;
	label->setParent(this);
	//设置字体
	QFont font;
	font.setFamily("华文新魏");
	font.setPointSize(20);
	QString levelstr = QString("LEVEL:%1").arg(levelindex);
	label->setText(levelstr);
	//加载字体
	label->setFont(font);
	label->setGeometry(30,this->height()-50,120,50);

	//初始化每个关卡的二维数组
	dataConfig config;
	for (int i = 0;i<4;i++)
	{
		for (int j = 0;j<4;j++)
		{	//把按钮的状态保存下来
			gameArry[i][j] = config.mData[this->levelindex][i][j];
		}
	}

	//显示金币背景图
	for (int i = 0;i<4;i++)
	{
		for (int j = 0;j<4;j++)
		{
			//绘制背景图片
			QLabel* backlabel = new QLabel;
			backlabel->setGeometry(0,0,50,50);
			backlabel->setPixmap(QPixmap(":/res/BoardNode(1).png"));
			backlabel->setParent(this);
			backlabel->move(57+i*50,200+j*50);

			QString str;
			if (gameArry[i][j] == 1)
			{
				//显示金币
				str = ":/res/Coin0001.png";
			}
			else
			{
				//显示银币
				str = ":/res/Coin0008.png";
			}

			//创建金币
			MyCoin* coin = new MyCoin(str);
			coin->setParent(this);
			coin->move(59+i*50,204+j*50);
		}
	}
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
