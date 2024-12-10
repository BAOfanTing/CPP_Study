#include "mainwindow.h"

mainwindow::mainwindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    ////设置单选默认选中
    //ui.rBtnMan->setChecked(true);

    ////点击显示信息。
    //connect(ui.rBtnWoman,&QRadioButton::clicked,[=](){
    //    qDebug() << "选中女的了";
    //});

    ////多选按钮,2是选中，0是未选中
    //connect(ui.checkBox_4, &QCheckBox::stateChanged, [=](int state) {
    //    qDebug() << state;
    //    });


    ////利用listWidget写诗
    //QListWidgetItem* item = new QListWidgetItem("锄禾日当午");
    ////将一行诗放入
    //ui.listWidget->addItem(item);
    //item->setTextAlignment(Qt::AlignHCenter);

    QStringList list;
    list <<"锄禾日当午"<<"汗滴禾下午"<<"ashjdfjh";
    ui.listWidget->addItems(list);
}

mainwindow::~mainwindow()
{}
