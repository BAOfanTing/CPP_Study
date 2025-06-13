#include "mygraphicslineitem.h"
#include <QCursor>
#include <QGraphicsSceneHoverEvent>
#include "logitem.h"
#include "Config.h"
#include <QPen>

int MyGraphicsLineItem::lineCounter = 1;

MyGraphicsLineItem::MyGraphicsLineItem(const QLineF &line, QGraphicsItem *parent)
    :QGraphicsLineItem(line,parent)
{
	setPen(QPen(Config::itemColor, Config::lineWidth));
	setFlags(QGraphicsItem::ItemIsMovable); //可以拖动
    setAcceptHoverEvents(true);//接收鼠标悬浮

    //名称
    m_strLabelText = QString(QObject::tr("Line %1").arg(lineCounter++));
	m_itmLabel = new QGraphicsTextItem(m_strLabelText,this);
    //移至中间
    QPointF center = line.center();
	m_itmLabel->setPos(center.x(),center.y()-5);
	m_itmLabel->setDefaultTextColor(Config::textColor);
}
/***********************************************
 * @功能描述 : 设置图形是否可拉伸
 * @创建者   : 石桢楠
 * @创建时间 : 2025-06-13
 * @参数     : none
 * @返回值   : none
 ***********************************************/
void MyGraphicsLineItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
	//打印场景坐标到日志
	// 获取线的局部坐标
	QLineF l = this->line();
	//坐标转换,把局部坐标转换到场景
	QPointF startPoint = this->mapToScene(l.p1());
	QPointF endPoint = this->mapToScene(l.p2());
	//日志打印坐标
	if (m_bFirstEnter)
	{
		LogItem::getInstance()->appendLog(QString("%1 第一个点(%2,%3),第二个点(%4,%5)")
			.arg(m_strLabelText)
			.arg(startPoint.x())
			.arg(startPoint.y())
			.arg(endPoint.x())
			.arg(endPoint.y()));
		m_bFirstEnter = false;
	}

    qreal edgeMargin = 10.0;//计算差值
    bool m_bNearLeft = (l.p1() - event->pos()).manhattanLength() < edgeMargin;
    bool m_bNearRight = (l.p2() - event->pos()).manhattanLength() < edgeMargin;

    //移动左点还是右点
    if(m_bNearLeft)
    {
        m_bLeftResizing = true;
        setCursor(QCursor(Qt::SizeHorCursor));
    }
    else if(m_bNearRight)
    {
        m_bRightResizing = true;
        setCursor(QCursor(Qt::SizeHorCursor));
    }
    else
    {
        m_bLeftResizing = false;
        m_bRightResizing = false;
        setCursor(QCursor(Qt::OpenHandCursor));
        QGraphicsLineItem::hoverMoveEvent(event);//保留父类的默认行为
    }
}

void MyGraphicsLineItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //第一次点击记录位置
    if(!m_bLeftResizing && !m_bRightResizing)
    {
        QGraphicsLineItem::mousePressEvent(event);//保留父类的默认行为
    }
    m_lastMousePos = event->pos();
}
/***********************************************
 * @功能描述 : 鼠标按住移动拉伸图形
 * @创建者   : 石桢楠
 * @创建时间 : 2025-06-13
 * @参数     : none
 * @返回值   : none
 ***********************************************/
void MyGraphicsLineItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QLineF l = line();
    if(m_bLeftResizing)
    {
         QPointF delta = event->pos()-m_lastMousePos; //两次鼠标位置的差值
         l.setP1(l.p1()+delta);
         setLine(l);  // 更新线段
         m_lastMousePos = event->pos();
         updateLabel();
    }
    else if(m_bRightResizing)
    {
        QPointF delta = event->pos()-m_lastMousePos; //两次鼠标位置的差值
        l.setP2(l.p2()+delta);
        setLine(l);  // 更新线段
        m_lastMousePos = event->pos();
        updateLabel();
    }
    else
    {
        QGraphicsLineItem::mouseMoveEvent(event);//保留父类的默认行为
    }
}

void MyGraphicsLineItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_bLeftResizing = false;
    m_bRightResizing = false;
    QGraphicsLineItem::mouseReleaseEvent(event);//保留父类的默认行为
}

/***********************************************
 * @功能描述 : 鼠标离开可以打印坐标
 * @创建者   : 石桢楠
 * @创建时间 : 2025-06-13
 * @参数     : none
 * @返回值   : none
 ***********************************************/
void MyGraphicsLineItem::hoverLeaveEvent(QGraphicsSceneHoverEvent * event)
{
	m_bFirstEnter = true;
	QGraphicsLineItem::hoverLeaveEvent(event);
}

/***********************************************
 * @功能描述 : 更新名称位置在线中间
 * @创建者   : 石桢楠
 * @创建时间 : 2025-06-13
 * @参数     : none
 * @返回值   : none
 ***********************************************/
void MyGraphicsLineItem::updateLabel()
{
    QPointF center = line().center();
    m_itmLabel->setPos(center.x(), center.y() - 5);
}

