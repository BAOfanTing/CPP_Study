#include "Student.h"


Student::Student(QObject *parent)
	: QObject(parent)
{}

Student::~Student()
{}

void Student::treat()
{
	qDebug("请老师吃饭");
}

void Student::treat(QString foodname)
{
	//QString -> char *先砖成QByteArray(.toutf8())再转char * (.data())
	qDebug()<<"请老师吃饭"<<foodname.toUtf8().data();
}
