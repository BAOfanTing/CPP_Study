#include "mainWidget.h"


mainWidget::mainWidget(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    
    ////pixmap绘图设备
    //QPixmap pix(300,300);

    ////填充背景颜色
    //pix.fill(Qt::white);

    ////声明画家
    //QPainter painter(&pix);
    //painter.setPen(QPen(Qt::green));
    //painter.drawEllipse(QPoint(150,150),100,100);

    ////保存
    //pix.save("E:\\pix.png");

 //-----------------------------------------------------------

 //   //QImage绘图
 //   QImage img( 300, 300, QImage::Format_RGB32);
 //   img.fill(Qt::yellow);

	////声明画家
	//QPainter painter(&img);
	//painter.setPen(QPen(Qt::red));
	//painter.drawEllipse(QPoint(150,150),100,100);

	////保存
	//img.save("E:\\img.png");


    //QPicter绘图设备，可以记录和重新绘图指令
    QPicture pic;
    QPainter painter;
    painter.begin(&pic); //开始往上画
	painter.setPen(QPen(Qt::cyan));
	painter.drawEllipse(QPoint(150, 150), 100, 100);
    painter.end();//结束画画

    //保存在磁盘
    pic.save("E:\\pic.zt");




}

mainWidget::~mainWidget()
{}

void mainWidget::paintEvent(QPaintEvent*)
{
    ////绘图窗口
    //QPainter painter(this);

    ////利用QImage修改像素
    //QImage img;
    //img.load(":Image/butterfly.png");

    ////修改像素点
    //for (int i = 50; i<100;i++)
    //{
    //    for (int j = 50; j<100;j++)
    //    {
    //        //设置像素点的值
    //        QRgb value = qRgb(255,0,0);
    //        img.setPixel(i,j,value);
    //    }
    //}
    //painter.drawImage(0,0,img);



    QPainter painter(this);
    //重现QPicture指令
    QPicture pic;
    pic.load("E:\\pic.zt");
    painter.drawPicture(0,0,pic);

}
