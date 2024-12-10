#include "MainWindow.h"
#pragma execution_character_set("utf-8")

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	//ui.actionnew->setIcon(QIcon("C:/Users/BAOfanTing/Desktop/Image/Luffy.png"));
	// 
	//使用添加qt资源  ":+前缀名+文件名"
	ui.actionnew->setIcon(QIcon(":/Image/Luffy.png"));
	ui.actiondaaki->setIcon(QIcon(":/Image/Luffy.png"));

 //   resize(600,400);

 //   //菜单栏创建
 //   QMenuBar* bar = menuBar();
 //   //将菜单栏放入窗口中
 //   setMenuBar(bar);
 //   //创建菜单
 //   QMenu* fileMenu = bar->addMenu("文件");
 //   QMenu* editMenu = bar->addMenu("编辑");

 //   //创建菜单子项
 //   fileMenu->addAction("新建");
 //   //添加分割线
 //   fileMenu->addSeparator();
 //   fileMenu->addAction("打开");


 //   //工具栏 可以有多个
 //   QToolBar* toolbar = new QToolBar(this);
 //   addToolBar(Qt::LeftToolBarArea,toolbar);
 //   //设置可以移动
 //   toolbar->setMovable(false);
 //   //设置子菜单
 //   toolbar->addAction("画图");
 //   //添加其他控件
 //   QPushButton* btn = new QPushButton("打开",this);
 //   toolbar->addWidget(btn);

 //   //状态栏，最多一个
 //   QStatusBar* stBar = new QStatusBar();
 //   //放置到窗口中
 //   setStatusBar(stBar);
 //   //放标签控件
 //   QLabel* label1 = new QLabel("提示信息",this);
 //   stBar->addWidget(label1);

	//QLabel* label2 = new QLabel("右侧提示信息", this);
	//stBar->addWidget(label2);

 //   //铆接（浮动框口），可以有多个
 //   QDockWidget* dockWidget = new QDockWidget("浮动",this);
 //   addDockWidget(Qt::BottomDockWidgetArea,dockWidget);//设置位置
 //   //限制后期停靠区域
 //   dockWidget->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);

 //   //设置中心部件只能一个
 //   QTextEdit* textedit = new QTextEdit(this);
 //   setCentralWidget(textedit);


}

MainWindow::~MainWindow()
{}
