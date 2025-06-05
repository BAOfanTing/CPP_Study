#include "mygraphicsview.h"
#include "mainwindow.h"
#include <QMouseEvent>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>


#include <mygraphicsellipseitem.h>
#include <mygraphicslineitem.h>
#include <mygraphicsrectitem.h>

MyGraphicsView::MyGraphicsView(MainWindow *window,QWidget *parent)
    : QGraphicsView(parent), m_window(window)
{
    setSceneRect(0, 0, 800, 600);  // 只允许场景显示在固定区域
    //判断绘制属性
    connect(m_window,&MainWindow::sig_DrawRect,[=](bool bTrue){m_bDrawRect =bTrue;});
    connect(m_window,&MainWindow::sig_DrawLine,[=](bool bTrue){m_bDrawLine =bTrue;});
    connect(m_window,&MainWindow::sig_DrawPoint,[=](bool bTrue){m_bDrawPoint =bTrue;});
}

//捕获鼠标绘图
void MyGraphicsView::mousePressEvent(QMouseEvent *event)
{
//    qDebug() << "Mouse button:" << event->buttons();
    //画矩形
    if(m_bDrawRect &&  event->buttons() == Qt::LeftButton)
    {
        QPointF scenePos = mapToScene(event->pos());
        QRectF rect(scenePos.x()-10,scenePos.y()-10,80,80);//以鼠标中心4040绘制矩形

        MyGraphicsRectItem *item = new MyGraphicsRectItem(rect);
        item->setPen(QPen(Qt::red,4));
        item->setBrush(QBrush(Qt::transparent));
        item->setFlags(QGraphicsItem::ItemIsMovable); //可以拖动
        this->scene()->addItem(item);

        m_bDrawRect = false;//只绘制一次
    }
    //画线
    if(m_bDrawLine &&  event->buttons() == Qt::LeftButton)
    {
        QPointF scenePos = mapToScene(event->pos());
        QLineF line(scenePos,scenePos+QPointF(100,0));
        MyGraphicsLineItem *item = new MyGraphicsLineItem(line);
        item->setPen(QPen(Qt::red,4));
        item->setFlags(QGraphicsItem::ItemIsMovable); //可以拖动
        scene()->addItem(item);

        m_bDrawLine = false;//只绘制一次
    }
    //画点
    if(m_bDrawPoint &&  event->buttons() == Qt::LeftButton)
    {
        QPointF scenePos = mapToScene(event->pos());
        qreal radius = 10;
        MyGraphicsEllipseItem *point = new MyGraphicsEllipseItem(scenePos.x(),scenePos.y(),2*radius,2*radius);
        point->setBrush(Qt::red);
        point->setFlags(QGraphicsItem::ItemIsMovable); //可以拖动
        scene()->addItem(point);

        m_bDrawPoint = false;//只绘制一次
    }
    QGraphicsView::mousePressEvent(event);//保留父类的默认行为
}

