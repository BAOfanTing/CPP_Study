#include "mygraphicsellipseitem.h"
#include <QCursor>
#include "logitem.h"
#include "Config.h"
#include <QBrush>

int MyGraphicsEllipseItem::pointCounter = 1;

MyGraphicsEllipseItem::MyGraphicsEllipseItem(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent)
 : QGraphicsEllipseItem(x, y, w, h, parent)
{
    setAcceptHoverEvents(true);						//允许悬浮事件
	this->setBrush(Config::itemColor);
	this->setFlags(QGraphicsItem::ItemIsMovable);	//可以拖动
    //名称
    m_strLabelText = QString(QObject::tr("Point %1").arg(pointCounter++));
	m_itmLabel = new QGraphicsTextItem(m_strLabelText,this);
    //移至右上角
    QPointF topRight = rect().topRight();
	m_itmLabel->setPos(topRight.x(),topRight.y()-10);
	m_itmLabel->setDefaultTextColor(Config::textColor);
}

/***********************************************
 * @功能描述 : 鼠标首次进入打印顶点坐标
 * @创建者   : 石桢楠
 * @创建时间 : 2025-06-13
 * @参数     : none
 * @返回值   : none
 ***********************************************/
void MyGraphicsEllipseItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(QCursor(Qt::OpenHandCursor));			//设置鼠标样式
    QGraphicsEllipseItem::hoverEnterEvent(event);	//保留父类的默认行为

	//打印场景坐标到日志
	QPointF localcenter = this->rect().center();	//椭圆中心坐标
	QPointF sceneCenter = this->mapToScene(localcenter);

	//日志打印坐标
	if (m_bFirstEnter)
	{
		LogItem::getInstance()->appendLog(QString("%1 的坐标(%2,%3)").arg(m_strLabelText).arg(sceneCenter.x()).arg(sceneCenter.y()));
		m_bFirstEnter = false;
	}
}
/***********************************************
 * @功能描述 : 鼠标离开,设置打印日志
 * @创建者   : 石桢楠
 * @创建时间 : 2025-06-13
 * @参数     : none
 * @返回值   : none
 ***********************************************/
void MyGraphicsEllipseItem::hoverLeaveEvent(QGraphicsSceneHoverEvent * event)
{
	m_bFirstEnter = true;
	QGraphicsEllipseItem::hoverLeaveEvent(event);
}
