#include "mygraphicslineitem.h"
#include <QCursor>
#include <QGraphicsSceneHoverEvent>
#include "logitem.h"

int MyGraphicsLineItem::lineCounter = 1;

MyGraphicsLineItem::MyGraphicsLineItem(const QLineF &line, QGraphicsItem *parent)
    :QGraphicsLineItem(line,parent)
{
    setAcceptHoverEvents(true);//接收鼠标悬浮

    //名称
    labelText = QString(QObject::tr("Line %1").arg(lineCounter++));
    m_label = new QGraphicsTextItem(labelText,this);
    //移至中间
    QPointF center = line.center();
    m_label->setPos(center.x(),center.y()-5);
    m_label->setDefaultTextColor(Qt::red);
}

void MyGraphicsLineItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
	//打印场景坐标到日志
	// 获取线的局部坐标
	QLineF l = this->line();
	//坐标转换,把局部坐标转换到场景
	QPointF startPoint = this->mapToScene(l.p1());
	QPointF endPoint = this->mapToScene(l.p2());
	//日志打印坐标
	LogItem::getInstance()->appendLog(QString("%1 第一个点(%2,%3),第二个点(%4,%5)").arg(labelText)
																		.arg(startPoint.x()) 
																		.arg(startPoint.y())
																		.arg(endPoint.x())
																		.arg(endPoint.y()));

    qreal edgeMargin = 10.0;//计算差值
    bool nearLeft = (l.p1() - event->pos()).manhattanLength() < edgeMargin;
    bool nearRight = (l.p2() - event->pos()).manhattanLength() < edgeMargin;

    //移动左点还是右点
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
         updateLabel();
    }
    else if(m_Right_resizing)
    {
        QPointF delta = event->pos()-m_lastMousePos;
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
    m_Left_resizing = false;
    m_Right_resizing = false;
    QGraphicsLineItem::mouseReleaseEvent(event);//保留父类的默认行为
}

//更新文本位置
void MyGraphicsLineItem::updateLabel()
{
    QPointF center = line().center();
    m_label->setPos(center.x(), center.y() - 5);
}
