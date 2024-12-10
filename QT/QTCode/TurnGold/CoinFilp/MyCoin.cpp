#include "MyCoin.h"

//MyCoin::MyCoin(QWidget *parent)
//	: QPushButton(parent)
//{}

MyCoin::~MyCoin()
{}

MyCoin::MyCoin(QString btnImg)
{
	QPixmap pix;
	bool ref = pix.load(btnImg);
	if (!ref)
	{
		QString str = QString("%1 加载失败").arg(btnImg);
		qDebug() << str;
		return ;
	}
	this->setFixedSize(pix.width(),pix.height());
	this->setStyleSheet("QPushButton{border:0px}");
	this->setIcon(pix);
	this->setIconSize(QSize(pix.width(),pix.height()));
	
	//初始化定时器
	timer1 = new QTimer(this);
	timer2 = new QTimer(this);


	//监听正面翻反面的信号，并且反转金币
	connect(timer1,&QTimer::timeout,[=](){
		QPixmap pix;
		QString str = QString(":/res/Coin000%1.png").arg(min++);
		pix.load(str);
		this->setFixedSize(pix.width(),pix.height());
		this->setStyleSheet("QPushButton{border:0px}");
		this->setIcon(pix);
		this->setIconSize(QSize(pix.width(),pix.height()));
		//判断如果翻完了
		if (this->min > this->max)
		{
			this->min = 1;
			timer1->stop();
			this->isAnimation = false;
		}

	});

	//监听反面翻正面的信号，并且反转金币
	connect(timer2, &QTimer::timeout, [=]() {
		QPixmap pix;
		QString str = QString(":/res/Coin000%1.png").arg(max--);
		pix.load(str);
		this->setFixedSize(pix.width(), pix.height());
		this->setStyleSheet("QPushButton{border:0px}");
		this->setIcon(pix);
		this->setIconSize(QSize(pix.width(), pix.height()));
		//判断如果翻完了
		if (this->max < this->min  )
		{
			this->max = 8;
			timer2->stop();
			this->isAnimation = false;
		}
		});
}

void MyCoin::changeFlag()
{
	if (this->flag)
	{
		//正面翻反面
		this->flag = false;
		//启动定时器
		timer1->start(30);
		bool isAnimation = true;
	}
	else
	{
		//反面翻正面
		this->flag = true;
		//启动定时器
		timer2->start(30);
		bool isAnimation = true;
	}

}

void MyCoin::mousePressEvent(QMouseEvent* e)
{
	if (this->isAnimation)
	{
		return;
	}
	else
	{
		QPushButton::mousePressEvent(e);
	}
}
