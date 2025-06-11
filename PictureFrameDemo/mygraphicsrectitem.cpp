#include "mygraphicsrectitem.h"
#include <QCursor>
#include <QGraphicsSceneHoverEvent>
#include "logitem.h"
#include "Config.h"
#include <QBrush>
#include <QPen>

int MyGraphicsRectItem::rectCounter = 1;

MyGraphicsRectItem::MyGraphicsRectItem(const QRectF &rect, QGraphicsItem *parent)
    :QGraphicsRectItem(rect,parent)
{
    setAcceptHoverEvents(true);  //允许悬浮事件
	setPen(QPen(Config::itemColor, 4));
	setBrush(QBrush(Qt::transparent));
	setFlags(QGraphicsItem::ItemIsMovable); //可以拖动
    //名称
	m_strLabelText = QString(QObject::tr("Rect %1").arg(rectCounter++));
	m_itmLabel = new QGraphicsTextItem(m_strLabelText,this);
    //移至右上角
    QPointF topLeft = rect.topLeft();
	m_itmLabel->setPos(topLeft.x()-5,topLeft.y()-20);
	m_itmLabel->setDefaultTextColor(Config::textColor);
}

//检测鼠标是否靠近右下角
void MyGraphicsRectItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    QRectF r = rect();     //这个是局部坐标,使用它坐标不会变
    qreal edgeMargin = 20.0;

	QRectF rectInScene = this->sceneBoundingRect();			//使用场景坐标,能够随拖动进行变化
	//日志打印坐标
	LogItem::getInstance()->appendLog(QString("%1 左上角(%2,%3),右下(%4,%5)").arg(m_strLabelText)
																			.arg(rectInScene.topLeft().x())
																			.arg(rectInScene.topLeft().y())
																			.arg(rectInScene.bottomRight().x())
																			.arg(rectInScene.bottomRight().y()));

    bool nearRightBottom = QLineF(event->pos(), r.bottomRight()).length() < edgeMargin;//判断鼠标是否在右下角
    bool nearLeftTop = QLineF(event->pos(), r.topLeft()).length()  < edgeMargin;  //判断鼠标是否在左上角
    //能否进行大小调整
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

    if(m_RightResizing)//右下角缩放大小,简单
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
    else if(m_LeftResizing) //左上角缩放大小,需要考率矩形是以左上角为基点来绘制的
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
		m_itmLabel->setPos(newTopLeft.x()-5,newTopLeft.y()-20);
		m_itmLabel->setDefaultTextColor(Qt::red);
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



