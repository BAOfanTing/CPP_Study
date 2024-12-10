#include "widget.h"

widget::widget(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    //创建一个老师对象,右边的this是设置父类加入对象树
    this->te = new Teacher(this);

    //创建一个学生对象
    this->st = new Student(this);
    //搭建连接，要先连接在传递信号
    connect(te,&Teacher::hungry,st,&Student::treat);

    classisover();
}

widget::~widget()
{
    
}

void widget::classisover()
{
    //下课函数，调用后出发老师饿了的信号
    emit te->hungry();
}
