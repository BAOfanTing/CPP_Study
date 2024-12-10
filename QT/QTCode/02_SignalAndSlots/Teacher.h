#pragma once
#include <QObject>
class Teacher  : public QObject
{
	Q_OBJECT
public:
	Teacher(QObject *parent);
	~Teacher();
//自定义信号写到signals下
//返回值是void ，只需要声明，不需要实现
//可以有参数，可以重载
signals:
	void hungry();
};
