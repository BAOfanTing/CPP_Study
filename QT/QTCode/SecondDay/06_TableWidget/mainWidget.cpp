#include "mainWidget.h"

mainWidget::mainWidget(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    //设置列数
    ui.tableWidget->setColumnCount(3);

    //设置水平表头
    ui.tableWidget->setHorizontalHeaderLabels(QStringList() << "姓名"<<"性别" << "年龄");

    //设置行数
    ui.tableWidget->setRowCount(5);

    ////设置正文
    //ui.tableWidget->setItem(0,0,new QTableWidgetItem("亚瑟"));
    QStringList namelist;
    namelist <<"唐三"<<"李四"<<"消炎"<<"胖子" <<"瘦子";

    QList<QString> sexlist;
    sexlist<<"男"<<"女"<<"男"<<"女" <<"女";

    for (int i = 0; i < 5; i++)
    {
        int col = 0;
        ui.tableWidget->setItem(i,col++,new QTableWidgetItem(namelist[i]));
        ui.tableWidget->setItem(i,col++,new QTableWidgetItem(sexlist.at(i)));
        //int 转 QString
        ui.tableWidget->setItem(i,col++,new QTableWidgetItem(QString::number(i+18)));
    }
}

mainWidget::~mainWidget()
{}
