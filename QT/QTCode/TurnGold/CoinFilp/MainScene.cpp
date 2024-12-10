#include "MainScene.h"

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    //设置固定大小
    this->setFixedSize(320,580);
    //设置图片
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置框口标题
    this->setWindowTitle("老王带你翻金币");
    //退出按钮
    connect(ui.actionQuit,&QAction::triggered, [=]() {this->close(); });

    //开始按钮
    MyPushButton * startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.5+10);

    //实例化选择关卡场景
   
    //监听选择关卡的返回按钮信号，只需要建立一次连接
    connect(chooseScene,&chooselevelsene::chooseSceneBack,[=](){
        QTimer::singleShot(500, this, [=]() {
            chooseScene->hide();//隐藏显示关卡
            this->show();//显示主界面
         });
    });


    connect(startBtn, &QPushButton::clicked, [=]() {
        qDebug()<<"点击开始了";
        startBtn->zoom1();
        startBtn->zoom1(true);

        
        //延时，进入选择关卡场景
        QTimer::singleShot(500,this,[=](){
			//自身隐藏
			this->hide();
			//显示关卡
			chooseScene->show();
        });
        
    });

	/*connect(startBtn,&QPushButton::pressed,[=](){
		startBtn->move(this->width() * 0.5 - startBtn->width() * 0.5, this->height() * 0.5 + 15);
	});
	connect(startBtn, &QPushButton::released, [=]() {
		startBtn->move(this->width() * 0.5 - startBtn->width() * 0.5, this->height() * 0.5 + 10);
	});*/
}

MainScene::~MainScene()
{}

void MainScene::paintEvent(QPaintEvent*)
{
    //创建画家
    QPainter painter(this);
    //加载图片
    QPixmap pix;
    pix.load(QString(":/res/PlayLevelSceneBg.png"));

    //绘制背景
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/res/Title.png");
    //缩放图片
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    //绘制标题
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);


}
