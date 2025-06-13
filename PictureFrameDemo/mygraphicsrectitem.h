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
	void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

private:
    bool m_bRightResizing = false;		//右下能否缩放
    bool m_bLeftResizing = false;		//左下能否缩放
	bool m_bFirstEnter = true;			//鼠标进入首次打印坐标
    QPointF m_lastMousePos;				// 上一次鼠标位置

    static int rectCounter;				// 静态计数器

    QGraphicsTextItem *m_itmLabel;		//名称
	QString m_strLabelText;				//名称字符串

};

#endif // MYGRAPHICSRECTITEM_H
