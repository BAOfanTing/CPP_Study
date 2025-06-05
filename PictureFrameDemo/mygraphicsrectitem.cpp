#include "mygraphicsrectitem.h"
#include <QCursor>
#include <QGraphicsSceneHoverEvent>

int MyGraphicsRectItem::rectCounter = 1;

MyGraphicsRectItem::MyGraphicsRectItem(const QRectF &rect, QGraphicsItem *parent)
    :QGraphicsRectItem(rect,parent)
{
    setAcceptHoverEvents(true);  //允许悬浮事件
    //名称
    QString labelText = QString("矩形 %1").arg(rectCounter++);
    QGraphicsTextItem *label = new QGraphicsTextItem(labelText,this);
    //移至右上角
    QPointF topLeft = rect.topLeft();
    label->setPos(topLeft.x()+5,topLeft.y()-20);
    label->setDefaultTextColor(Qt::red);
}

//检测鼠标是否靠近右下角
void MyGraphicsRectItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    QRectF r = rect();
    qreal edgeMargin = 5.0;

    bool nearRight = qAbs(event->pos().x()-r.right()) < edgeMargin;//判断鼠标是否在右下角
    bool nearBottom = qAbs(event->pos().y()-r.bottom()) < edgeMargin;
    //能否进行缩放
    if(nearRight && nearBottom)
    {
        setCursor(QCursor(Qt::SizeFDiagCursor));
        m_resizing = true;
    }
    else
    {
        setCursor(QCursor(Qt::OpenHandCursor));
        m_resizing = false;
    }

    QGraphicsRectItem::hoverEnterEvent(event);//保留父类的默认行为
}

void MyGraphicsRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //第一次点击记录位置
    if(!m_resizing)
    {
        QGraphicsRectItem::mousePressEvent(event);//保留父类的默认行为
    }
    m_lastMousePos = event->pos();
}

void MyGraphicsRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_resizing)
    {
        //计算两次鼠标位置差值，扩大边
        QPointF delta = event->pos() - m_lastMousePos;
        QRectF r = rect();

        r.setRight(r.right() + delta.x());
        r.setBottom(r.bottom() + delta.y());

        setRect(r.normalized());
        m_lastMousePos = event->pos();//给下一次事件记录位置
    }
    else
    {
        QGraphicsRectItem::mouseMoveEvent(event);//保留父类的默认行为
    }

}

void MyGraphicsRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_resizing = false;
    QGraphicsRectItem::mouseReleaseEvent(event);//保留父类的默认行为
}



