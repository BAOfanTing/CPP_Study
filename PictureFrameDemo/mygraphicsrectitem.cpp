#include "mygraphicsrectitem.h"
#include <QCursor>
#include <QGraphicsSceneHoverEvent>

int MyGraphicsRectItem::rectCounter = 1;

MyGraphicsRectItem::MyGraphicsRectItem(const QRectF &rect, QGraphicsItem *parent)
    :QGraphicsRectItem(rect,parent)
{
    setAcceptHoverEvents(true);  //允许悬浮事件
    //名称
    QString labelText = QString(QObject::tr("Rect %1").arg(rectCounter++));
    label = new QGraphicsTextItem(labelText,this);
    //移至右上角
    QPointF topLeft = rect.topLeft();
    label->setPos(topLeft.x()-5,topLeft.y()-20);
    label->setDefaultTextColor(Qt::red);
}

//检测鼠标是否靠近右下角
void MyGraphicsRectItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    QRectF r = rect();
    qreal edgeMargin = 20.0;

    bool nearRightBottom = QLineF(event->pos(), r.bottomRight()).length() < edgeMargin;//判断鼠标是否在右下角
    bool nearLeftTop = QLineF(event->pos(), r.topLeft()).length()  < edgeMargin;  //判断鼠标是否在左上角
    //能否进行缩放
    if(nearRightBottom)
    {
        setCursor(QCursor(Qt::SizeFDiagCursor));
        m_RightResizing = true;
        m_LeftResizing = false;
    }
    else if(nearLeftTop)
    {
        setCursor(QCursor(Qt::SizeFDiagCursor));
        m_RightResizing = false;
        m_LeftResizing = true;
    }
    else
    {
        setCursor(QCursor(Qt::OpenHandCursor));
        m_RightResizing = false;
        m_LeftResizing = false;
    }
    QGraphicsRectItem::hoverEnterEvent(event);//保留父类的默认行为
}

void MyGraphicsRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //第一次点击记录位置
    if(!m_RightResizing && !m_LeftResizing)
    {
        QGraphicsRectItem::mousePressEvent(event);//保留父类的默认行为
    }
    m_lastMousePos = event->pos();
}

void MyGraphicsRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //最小高宽
    const qreal minWidth = 40.0;
    const qreal minHeight = 40.0;

    if(m_RightResizing)
    {
        //计算两次鼠标位置差值，扩大边
        QPointF delta = event->pos() - m_lastMousePos;
        QRectF r = rect();

        //限制最小缩放为40*40
        qreal newWidth = r.width() + delta.x();//计算新大小
        qreal newHeight = r.height() + delta.y();

        //取最大值
        newWidth = qMax(newWidth, minWidth);
        newHeight = qMax(newHeight, minHeight);
        r.setSize(QSizeF(newWidth,newHeight));

        setRect(r.normalized());
        m_lastMousePos = event->pos();//给下一次事件记录位置
    }
    else if(m_LeftResizing)
    {
        //计算两次鼠标位置差值，扩大边
        QPointF delta = event->pos() - m_lastMousePos;
        QRectF r = rect();

        //更新左上角基点坐标,左下角点的坐标不变
        QPointF newTopLeft = r.topLeft()+delta;
        QPointF bottomRight = r.bottomRight();

        //计算新高宽
        qreal newWidth = bottomRight.x() - newTopLeft.x();
        qreal newHeight = bottomRight.y() - newTopLeft.y();

        //判断缩放最小
        if(newWidth < minWidth)
        {
            newTopLeft.setX(bottomRight.x() - minWidth);//以左下角点+40为值设置新的基点xy
        }
        if(newHeight < minHeight)
        {
            newTopLeft.setY(bottomRight.y() - minHeight);
        }

        QRectF newRect(newTopLeft,bottomRight);
        setRect(newRect.normalized());

        //左上角拉伸时名称跟随
        label->setPos(newTopLeft.x()-5,newTopLeft.y()-20);
        label->setDefaultTextColor(Qt::red);
        m_lastMousePos = event->pos();
    }
    else
    {
        QGraphicsRectItem::mouseMoveEvent(event);//保留父类的默认行为
    }

}

void MyGraphicsRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_RightResizing = false;
    m_LeftResizing = false;
    QGraphicsRectItem::mouseReleaseEvent(event);//保留父类的默认行为
}



