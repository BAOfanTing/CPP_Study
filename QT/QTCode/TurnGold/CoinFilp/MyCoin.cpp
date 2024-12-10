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
		
}
