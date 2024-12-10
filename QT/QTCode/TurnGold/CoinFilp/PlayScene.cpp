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

	//加载胜利背景图
	QLabel* winlabel = new QLabel;
	QPixmap winpix;
	winpix.load(":/res/LevelCompletedDialogBg.png");
	winlabel->setGeometry(0,0,winpix.width(),winpix.height());
	winlabel->setPixmap(winpix);
	winlabel->setParent(this);
	winlabel->move((this->width()- winpix.width())*0.5,-winpix.height());


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
			
			//给金币赋值
			coin->posX = i;
			coin->posY = j;
			coin->flag = gameArry[i][j];// 1是正面，2是反面

			//将金币放入到金币的二维数组中
			coinbtn[i][j] = coin;

			//连接点击
			connect(coin,&MyCoin::clicked,[=](){
				coin->changeFlag();
				//更新flag
				this->gameArry[i][j] = this->gameArry[i][j] == 0 ? 0 : 1;


				//反转周围金币,延时反转
				QTimer::singleShot(300,[=](){
					//反转右侧
					if (coin->posX + 1 <= 3)
					{
						coinbtn[coin->posX + 1][coin->posY]->changeFlag();
						this->gameArry[coin->posX + 1][coin->posY] = this->gameArry[coin->posX + 1][coin->posY] == 0 ? 0 : 1;
					}
					//反转左侧
					if (coin->posX - 1 >= 0)
					{
						coinbtn[coin->posX - 1][coin->posY]->changeFlag();
						this->gameArry[coin->posX - 1][coin->posY] = this->gameArry[coin->posX - 1][coin->posY] == 0 ? 0 : 1;
					}
					//反转上侧
					if (coin->posY - 1 >= 0)
					{
						coinbtn[coin->posX][coin->posY - 1]->changeFlag();
						this->gameArry[coin->posX][coin->posY - 1] = this->gameArry[coin->posX][coin->posY - 1] == 0 ? 0 : 1;
					}
					//反转下侧
					if (coin->posY + 1 <= 3)
					{
						coinbtn[coin->posX][coin->posY + 1]->changeFlag();
						this->gameArry[coin->posX][coin->posY + 1] = this->gameArry[coin->posX][coin->posY + 1] == 0 ? 0 : 1;
					}

					//判断是否胜利
					this->isWin = true;
					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 4; j++)
						{
							if (coinbtn[i][j]->flag == false)
							{
								this->isWin = false;
								i = 5;
								break;
							}
						}
					}
					if (this->isWin)
					{
						qDebug() << "游戏胜利";
						//胜利后不能点击金币
						for (int i = 0; i < 4; i++)
						{
							for (int j = 0; j < 4; j++)
							{
								coinbtn[i][j]->Canclick = false;
							}
						}

						//创建动态特效
						QPropertyAnimation* animation = new QPropertyAnimation(winlabel, "geometry");
						//设置时间间隔
						animation->setDuration(1000);
						//起始位置
						animation->setStartValue(QRect(winlabel->x(),winlabel->y(),winlabel->width(),winlabel->height()));
						//结束位置
						animation->setEndValue(QRect(winlabel->x(), winlabel->y()+200, winlabel->width(), winlabel->height()));
						//设置弹跳曲线
						animation->setEasingCurve(QEasingCurve::OutBounce);
						//执行动画
						animation->start();
					}
				});
			});
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
