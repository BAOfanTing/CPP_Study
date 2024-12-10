#pragma once

#include <QObject>
#include <QDebug>
#include <QString>
class Student  : public QObject
{
public:
	Student(QObject *parent);
	~Student();
public slots:
	//返回值void ，需要声明，也需要实现
	//可以有参数，可以发生重载
	void treat();
	void treat(QString foodname);
};
