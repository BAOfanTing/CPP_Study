#include "mainWidget.h"

mainWidget::mainWidget(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    //点击按钮弹出文件对话框
    connect(ui.pushButton,&QPushButton::clicked,[=](){
    
        QString path = QFileDialog::getOpenFileName(this,"打开文件",":/132.txt");
        //将路径放到lineedit中
        ui.lineEdit->setText(path);

        //读取内容，放入textedit
        //Qfile默认格式是UTF-8
        

        QFile file(path);//参数就是读取路径
        //设置打开方式
        file.open(QIODeviceBase::ReadOnly);
        
       
        /*QByteArray array =  file.readAll();*/
        QByteArray array;
        while (!file.atEnd()) 
        {
            array += file.readLine();
        }

        //将读到的数据放入到textedit中
        //QString content = QString::fromLocal8Bit(array); //读取gkb格式用这个
        ui.textEdit->setText(array);
        //关闭
        file.close();


        ////进行写文件
        //file.open(QIODeviceBase::Append);
        //file.write("啊啊啊啊啊啊啊啊啊啊啊啊啊");
        //file.close();


        //QFileInfo文件信息类
        QFileInfo info(file);

        qDebug() <<"大小："<< info.size() <<"name :" << info.fileName() <<"houzhui:" << info.suffix();
        qDebug() << "创建日期：" << info.birthTime().toString("yyyy/mm/dd");
        qDebug() << "最后修改日期：" << info.lastModified().toString("yyyy-mm-dd");

    });
}

mainWidget::~mainWidget()
{}
