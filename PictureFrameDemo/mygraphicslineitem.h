#ifndef MYGRAPHICSLINEITEM_H
#define MYGRAPHICSLINEITEM_H

#include <QObject>
#include <QGraphicsLineItem>

class MyGraphicsLineItem : public QGraphicsLineItem
{
public:
    MyGraphicsLineItem(const QLineF &line, QGraphicsItem *parent = nullptr);

    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;//重写鼠标悬浮
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    void updateLabel();

private:
    bool m_Left_resizing = false;
    bool m_Right_resizing = false;
    QPointF m_lastMousePos;        // 上一次鼠标位置

    static int lineCounter;
    QGraphicsTextItem *m_label;
	QString labelText;			//名称字符串
};

#endif // MYGRAPHICSLINEITEM_H
