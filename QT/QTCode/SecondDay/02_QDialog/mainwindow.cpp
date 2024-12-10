#include "mainwindow.h"

mainwindow::mainwindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    //点击新建，弹出一个对话框
    
    connect(ui.NewCreate, &QAction::triggered, [=]() {
	    //模态对话框（不可以对其他窗口进行操作阻塞代码) 非模态对话框（可以对其他窗口进行操作)
        
        //模态创建
		/*QDialog dlg(this);
		dlg.resize(200, 100);
		dlg.exec();
		qDebug() <<"对话模态框弹出了";*/
        
        //非模态创建.在函数中show后对象就不存在了，所以需要在堆区创建这个对话框
		//QDialog* dlg2 = new QDialog(this);
  //      dlg2->resize(200, 100);
  //      dlg2->show();
  //      //设置属性，点击关闭时释放内存
  //      dlg2->setAttribute(Qt::WA_DeleteOnClose);
		//qDebug() << "对话非模态框弹出了";

        //消息对话框
        //错误对话框
        QMessageBox::critical(this,"错误","错误");

        //信息对话框
        /*QMessageBox::information(this,"info","信息");*/

        //警告对话框
        /*QMessageBox::warning(this, "warn", "警告");*/

        //提问对话框
		//参数1父亲  参数2标题  参数3提示内容  参数4按键类型  参数5默认关联回车按键
        /*QMessageBox::question(this,"ques","提问",QMessageBox::Save |QMessageBox::Cancel,QMessageBox::Cancel);*/

       

        });
}

mainwindow::~mainwindow()
{}
