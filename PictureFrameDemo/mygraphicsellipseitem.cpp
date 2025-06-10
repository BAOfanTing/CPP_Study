#include "mygraphicsellipseitem.h"
#include <QCursor>
#include "logitem.h"

int MyGraphicsEllipseItem::pointCounter = 1;

MyGraphicsEllipseItem::MyGraphicsEllipseItem(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent)
 : QGraphicsEllipseItem(x, y, w, h, parent)
{
    setAcceptHoverEvents(true);  //允许悬浮事件

    //名称
    labelText = QString(QObject::tr("Point %1").arg(pointCounter++));
    label = new QGraphicsTextItem(labelText,this);
    //移至右上角
    QPointF topRight = rect().topRight();
    label->setPos(topRight.x(),topRight.y()-10);
    label->setDefaultTextColor(Qt::red);
}

void MyGraphicsEllipseItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(QCursor(Qt::OpenHandCursor));
    QGraphicsEllipseItem::hoverEnterEvent(event);//保留父类的默认行为

	//打印场景坐标到日志
	QPointF localcenter = this->rect().center();  //椭圆中心坐标
	QPointF sceneCenter = this->mapToScene(localcenter);

	//日志打印坐标
	LogItem::getInstance()->appendLog(QString("%1 的坐标(%2,%3)").arg(labelText).arg(sceneCenter.x()).arg(sceneCenter.y()));
}
