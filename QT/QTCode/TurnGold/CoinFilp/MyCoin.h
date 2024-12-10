#pragma once

#include <QObject>
#include <QPushButton>
class MyCoin  : public QPushButton
{
	Q_OBJECT

public:
	/*MyCoin(QWidget *parent);*/
	~MyCoin();
	//显示的是金币还是银币
	MyCoin(QString btnImg);
};
