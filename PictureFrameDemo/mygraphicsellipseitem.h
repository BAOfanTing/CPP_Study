#ifndef MYGRAPHICSELLIPSEITEM_H
#define MYGRAPHICSELLIPSEITEM_H

//使用椭圆来代替点

#include <QObject>
#include <QGraphicsEllipseItem>


class MyGraphicsEllipseItem : public QGraphicsEllipseItem
{
public:
    MyGraphicsEllipseItem(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent = nullptr);

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;//重写鼠标悬浮

private:
    static int pointCounter;
	QString m_strLabelText;			//名称字符串
	QGraphicsTextItem *m_itmLabel;	//名称
};

#endif // MYGRAPHICSELLIPSEITEM_H
