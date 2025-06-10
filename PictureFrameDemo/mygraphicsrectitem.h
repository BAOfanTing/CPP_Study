#ifndef MYGRAPHICSRECTITEM_H
#define MYGRAPHICSRECTITEM_H

#include <QGraphicsRectItem>


class MyGraphicsRectItem : public QGraphicsRectItem
{
public:
    MyGraphicsRectItem(const QRectF &rect, QGraphicsItem *parent = nullptr);

    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;//重写鼠标悬浮
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    bool m_RightResizing = false;
    bool m_LeftResizing = false;
    QPointF m_lastMousePos;        // 上一次鼠标位置

    static int rectCounter;  // 静态计数器

    QGraphicsTextItem *label; //名称
	QString labelText;		//名称字符串
};

#endif // MYGRAPHICSRECTITEM_H
