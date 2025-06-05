#include "mygraphicslineitem.h"
#include <QCursor>
#include <QGraphicsSceneHoverEvent>

int MyGraphicsLineItem::lineCounter = 1;

MyGraphicsLineItem::MyGraphicsLineItem(const QLineF &line, QGraphicsItem *parent)
    :QGraphicsLineItem(line,parent)
{
    setAcceptHoverEvents(true);//接收鼠标悬浮

    //名称
    QString labelText = QString("线 %1").arg(lineCounter++);
    QGraphicsTextItem *label = new QGraphicsTextItem(labelText,this);
    //移至中间
    QPointF center = line.center();
    label->setPos(center.x(),center.y()-5);
    label->setDefaultTextColor(Qt::red);
}

void MyGraphicsLineItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    QLineF l = line();
    qreal edgeMargin = 10.0;//计算差值
    bool nearLeft = (l.p1() - event->pos()).manhattanLength() < edgeMargin;
    bool nearRight = (l.p2() - event->pos()).manhattanLength() < edgeMargin;

    if(nearLeft)
    {
        m_Left_resizing = true;
        setCursor(QCursor(Qt::SizeHorCursor));
    }
    else if(nearRight)
    {
        m_Right_resizing = true;
        setCursor(QCursor(Qt::SizeHorCursor));
    }
    else
    {
        m_Left_resizing = false;
        m_Right_resizing = false;
        setCursor(QCursor(Qt::OpenHandCursor));
        QGraphicsLineItem::hoverMoveEvent(event);//保留父类的默认行为
    }
}


void MyGraphicsLineItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //第一次点击记录位置
    if(!m_Left_resizing && !m_Right_resizing)
    {
        QGraphicsLineItem::mousePressEvent(event);//保留父类的默认行为
    }
    m_lastMousePos = event->pos();
}

void MyGraphicsLineItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QLineF l = line();
    if(m_Left_resizing)
    {
         QPointF delta = event->pos()-m_lastMousePos;
         l.setP1(l.p1()+delta);
         setLine(l);  // 更新线段
         m_lastMousePos = event->pos();
    }
    else if(m_Right_resizing)
    {
        QPointF delta = event->pos()-m_lastMousePos;
        l.setP2(l.p2()+delta);
        setLine(l);  // 更新线段
        m_lastMousePos = event->pos();
    }
    else
    {
        QGraphicsLineItem::mouseMoveEvent(event);//保留父类的默认行为
    }
}


void MyGraphicsLineItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_Left_resizing = false;
    m_Right_resizing = false;
    QGraphicsLineItem::mouseReleaseEvent(event);//保留父类的默认行为
}
