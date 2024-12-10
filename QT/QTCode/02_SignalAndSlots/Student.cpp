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
