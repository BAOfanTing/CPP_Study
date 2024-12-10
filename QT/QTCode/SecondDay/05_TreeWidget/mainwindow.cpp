#include "mainwindow.h"

mainwindow::mainwindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    //treeWidget树控件使用
    //设置水平头
    ui.treeWidget->setHeaderLabels(QStringList()<<"英雄"<<"英雄介绍");

    QTreeWidgetItem* liItem = new QTreeWidgetItem(QStringList()<<"力量");
    QTreeWidgetItem* mingItem = new QTreeWidgetItem(QStringList()<<"敏捷");
    QTreeWidgetItem* zhiItem = new QTreeWidgetItem(QStringList()<<"智力");

    //加载顶层的节点
    ui.treeWidget->addTopLevelItem(liItem);
    ui.treeWidget->addTopLevelItem(mingItem);
    ui.treeWidget->addTopLevelItem(zhiItem);

    //追加子节点
    QStringList heroL1;
    heroL1 <<"刚住被"<<"前排坦克，能吸收伤害造成伤害";
    QTreeWidgetItem* l1 = new QTreeWidgetItem(heroL1);
    liItem->addChild(l1);

	QStringList heroM1;
    heroM1 << "唐三" << "莫欺少年穷";
	QTreeWidgetItem* M1 = new QTreeWidgetItem(heroM1);
	mingItem->addChild(M1);

	QStringList heroM2;
	heroM2 << "消炎" << "三十年河东" << "厉害";
	QTreeWidgetItem* M2 = new QTreeWidgetItem(heroM2);
	mingItem->addChild(M2);
}

mainwindow::~mainwindow()
{}
