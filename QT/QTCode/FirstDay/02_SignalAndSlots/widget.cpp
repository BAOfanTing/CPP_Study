#include "widget.h"
#pragma execution_character_set("utf-8")

widget::widget(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

 //   //创建一个老师对象,右边的this是设置父类加入对象树
 //   this->te = new Teacher(this);

 //   //创建一个学生对象
 //   this->st = new Student(this);

 //   ////搭建连接，要先连接在传递信号
 //   //connect(te,&Teacher::hungry,st,&Student::treat);

 //   //classisover();

 //   //连接到带参数的信号和槽
 //   //函数指针指向函数地址
 //   void (Teacher:: *teacherSignal)(QString) = &Teacher::hungry;
 //   void (Student:: *studentSlot)(QString) = &Student::treat;

 //   connect(te, teacherSignal, st, studentSlot);
 //   classisover();

 //   //点击一个按钮下课
 //   QPushButton* btn = new QPushButton("下课",this);
 //   this->resize(600,400);

 //   //点击按钮，下课
 //   connect(btn,&QPushButton::clicked,this,&widget::classisover);


 //   //无参信号和槽连接
	////连接到带参数的信号和槽
	////函数指针指向函数地址
	//void (Teacher:: * teacherSignal)(void) = &Teacher::hungry;
	//void (Student:: * studentSlot)(void) = &Student::treat;
	//connect(te, teacherSignal, st, studentSlot);

	////信号连接信号
	//connect(btn, &QPushButton::clicked, te, teacherSignal);


	//作业点击打开新窗口，点击关闭。新建两个按钮一个打开一个关闭
	QPushButton* open= new QPushButton("Open",this);
	QPushButton* close = new QPushButton("close", this);
	//移动第二个按钮
	close->move(100,0);
	//新建窗口，不用附加parent
	QWidget* window2 = new QWidget();
	window2->setWindowTitle("window2");
	//查询手册，窗口显示show,关闭close
	connect(open,&QPushButton::clicked,window2,&QWidget::show);
	connect(close, &QPushButton::clicked, window2, &QWidget::close);

}


widget::~widget()
{
    
}

void widget::classisover()
{
    //下课函数，调用后出发老师饿了的信号
    emit te->hungry("gongbaojiding");
    
}

