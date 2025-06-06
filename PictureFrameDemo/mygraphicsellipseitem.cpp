#include "mygraphicsellipseitem.h"
#include <QCursor>
#include <QDebug>

int MyGraphicsEllipseItem::pointCounter = 1;

MyGraphicsEllipseItem::MyGraphicsEllipseItem(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent)
 : QGraphicsEllipseItem(x, y, w, h, parent)
{
    setAcceptHoverEvents(true);  //允许悬浮事件

    //名称
    QString labelText = QString("Point %1").arg(pointCounter++);
    QGraphicsTextItem *label = new QGraphicsTextItem(labelText,this);
    //移至右上角
    QPointF topRight = rect().topRight();
    label->setPos(topRight.x(),topRight.y()-10);
    label->setDefaultTextColor(Qt::red);
}

void MyGraphicsEllipseItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(QCursor(Qt::OpenHandCursor));
    QGraphicsEllipseItem::hoverEnterEvent(event);//保留父类的默认行为
}
