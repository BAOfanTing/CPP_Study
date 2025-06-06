#include "mygraphicsview.h"
#include "mainwindow.h"
#include <QMouseEvent>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QGraphicsScene>


#include <mygraphicsellipseitem.h>
#include <mygraphicslineitem.h>
#include <mygraphicsrectitem.h>
#include <logitem.h>

MyGraphicsView::MyGraphicsView(MainWindow *window,QWidget *parent)
    : QGraphicsView(parent), m_window(window)
{
    // 先创建并设置一个scene
    QGraphicsScene *scene = new QGraphicsScene(this);
    this->setScene(scene);
    QRectF viewRect = this->viewport()->rect();
    this->scene()->setSceneRect(0,0,viewRect.width(),viewRect.height());
    //判断绘制属性
    connect(m_window,&MainWindow::sig_DrawRect,[=](bool bTrue){m_bDrawRect =bTrue;});
    connect(m_window,&MainWindow::sig_DrawLine,[=](bool bTrue){m_bDrawLine =bTrue;});
    connect(m_window,&MainWindow::sig_DrawPoint,[=](bool bTrue){m_bDrawPoint =bTrue;});
    connect(m_window,&MainWindow::sig_CanScale,[=](int value){m_bCanScale = value;});
    connect(m_window,&MainWindow::sig_DrawIndex,[=](int index){switch (index)
        {
            case 0:
            m_bDrawRect = true;
            m_bDrawPoint =false;
            m_bDrawLine =false;
            break;
            case 1:
            m_bDrawRect = false;
            m_bDrawPoint =true;
            m_bDrawLine =false;
            break;
            case 2:
            m_bDrawRect = false;
            m_bDrawPoint =false;
            m_bDrawLine =true;
            break;
        }});
}

//捕获鼠标绘图
void MyGraphicsView::mousePressEvent(QMouseEvent *event)
{
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

//捕获滚轮缩放
void MyGraphicsView::wheelEvent(QWheelEvent *event)
{
    if(m_bCanScale)
    {
        const double scaleFactor = 1.15; //缩放因子
        if(event->angleDelta().y() > 0)
        {
            scale(scaleFactor,scaleFactor);  //放大
            LogItem::getInstance()->appendLog("放大场景");
        }
        else
        {
            scale(1.0 / scaleFactor,1.0 / scaleFactor); //缩小
            LogItem::getInstance()->appendLog("缩小场景");
        }
    }
    else
    {
        QGraphicsView::wheelEvent(event);//保留父类的默认行为
    }
}




