#include "mygraphicsview.h"
#include "mainwindow.h"
#include <QMouseEvent>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QGraphicsScene>

#include <mygraphicsellipseitem.h>
#include <mygraphicslineitem.h>
#include <mygraphicsrectitem.h>
#include <logitem.h>
#include "Config.h"

//view相当于画布的视野,scene相当于画布
MyGraphicsView::MyGraphicsView(MainWindow *window,QWidget *parent)
    : QGraphicsView(parent), m_window(window)
{
    // 先创建并设置一个scene
    QGraphicsScene *scene = new QGraphicsScene(this);
    this->setScene(scene);
    QRectF viewRect = this->viewport()->rect();
    this->scene()->setSceneRect(0,0,viewRect.width(),viewRect.height());

	this->setRenderHint(QPainter::Antialiasing, true);		//打开抗锯齿模式
	this->setDragMode(QGraphicsView::ScrollHandDrag);		//允许拖动场景

	
    //判断绘制属性
    connect(m_window,&MainWindow::sig_DrawRect,[=](bool bTrue){m_bDrawRect = bTrue;});
    connect(m_window,&MainWindow::sig_DrawLine,[=](bool bTrue){m_bDrawLine = bTrue;});
    connect(m_window,&MainWindow::sig_DrawPoint,[=](bool bTrue){m_bDrawPoint = bTrue;});
    connect(m_window,&MainWindow::sig_CanScale,[=](int value){m_nCanScale = value;});   //缩放图片
    connect(m_window,&MainWindow::sig_ShowImage,this,&MyGraphicsView::on_m_ppbtnSelectImageclicked);       //展示图片
    connect(m_window,&MainWindow::sig_DrawIndex,[=](int index){switch (index)           //combox形式选择绘制属性
        {
            case 0:
            m_bDrawRect = true;
            m_bDrawPoint =false;
            m_bDrawLine =false;
            break;
            case 1:
            m_bDrawRect = false;
            m_bDrawPoint =true;
            m_bDrawLine =false;
            break;
            case 2:
            m_bDrawRect = false;
            m_bDrawPoint =false;
            m_bDrawLine =true;
            break;
        }});
}

//捕获鼠标绘图
void MyGraphicsView::mousePressEvent(QMouseEvent *event)
{
    //画矩形
    if(m_bDrawRect &&  event->buttons() == Qt::LeftButton)
    {
        QPointF scenePos = mapToScene(event->pos());
        QRectF rect(scenePos.x()-10,scenePos.y()-10,Config::rectSize, Config::rectSize);//以鼠标中心4040绘制矩形

        MyGraphicsRectItem *item = new MyGraphicsRectItem(rect);
        this->scene()->addItem(item);
        LogItem::getInstance()->appendLog("框已绘制");

        m_bDrawRect = false;//只绘制一次
    }
    //画线
    if(m_bDrawLine &&  event->buttons() == Qt::LeftButton)
    {
        QPointF scenePos = mapToScene(event->pos());
        QLineF line(scenePos,scenePos+QPointF(100,0));
        MyGraphicsLineItem *lineItem = new MyGraphicsLineItem(line);
        scene()->addItem(lineItem);
        LogItem::getInstance()->appendLog("线已绘制");

        m_bDrawLine = false;//只绘制一次
    }
    //画点
    if(m_bDrawPoint &&  event->buttons() == Qt::LeftButton)
    {
        QPointF scenePos = mapToScene(event->pos());
		//创建点
        MyGraphicsEllipseItem *point = new MyGraphicsEllipseItem(scenePos.x(),scenePos.y(),2*Config::pointSize, 2 * Config::pointSize);
        scene()->addItem(point);					//添加点到场景
        LogItem::getInstance()->appendLog("点已绘制");

        m_bDrawPoint = false;//只绘制一次
    }
    QGraphicsView::mousePressEvent(event);//保留父类的默认行为
}


/***********************************************
 * @功能描述 : 捕获滚轮缩放场景
 * @创建者   : 石桢楠
 * @创建时间 : 2025-06-13
 * @参数     : none
 * @返回值   : none
 ***********************************************/
void MyGraphicsView::wheelEvent(QWheelEvent *event)
{
    if(m_nCanScale)
    {
        const double scaleFactor = 1.15; //缩放因子
        if(event->angleDelta().y() > 0)
        {
            scale(scaleFactor,scaleFactor);  //放大
            LogItem::getInstance()->appendLog("放大场景");
        }
        else
        {
            scale(1.0 / scaleFactor,1.0 / scaleFactor); //缩小
            LogItem::getInstance()->appendLog("缩小场景");
        }
    }
    else
    {
        QGraphicsView::wheelEvent(event);//保留父类的默认行为
    }
}

//加载图片
void MyGraphicsView::on_m_ppbtnSelectImageclicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("open Image"), "",
                            tr("Image Files (*.png *.jpg *.jpeg *.bmp *.xpm)"));
    if (filename.isEmpty()) {
        return;
    }

    QImage image(filename);
    if (image.isNull()) {
        QMessageBox::warning(this, tr("error"), tr("Can't load Image: %1").arg(filename));
        return;
    }
    //场景二次初始化清空
    if (!this->scene()) {
        this->setScene(new QGraphicsScene(this));
    } else {
        this->scene()->clear();
    }
    //场景大小设置为视图大小
    QRectF viewRect = this->viewport()->rect();
    this->scene()->setSceneRect(0,0,viewRect.width(),viewRect.height());

    //缩放图片到场景大小
    QPixmap pixmap = QPixmap::fromImage(image);
    QSizeF targetsize = this->scene()->sceneRect().size();
    QPixmap scaledPixmap = pixmap.scaled(targetsize.toSize(),Qt::KeepAspectRatio,Qt::SmoothTransformation);

    //添加图片到场景
    QGraphicsPixmapItem *pixmapItem = this->scene()->addPixmap(scaledPixmap);

    //让图片在场景中居中
    QRectF sceneRect = this->scene()->sceneRect();
    QRectF pixmapRect = pixmapItem->boundingRect(); //获取图像高宽
    qreal x = (sceneRect.width() -pixmapRect.width())/2.0;//计算放置位置
    qreal y = (sceneRect.height() -pixmapRect.height())/2.0;

    pixmapItem->setPos(x,y);
}







