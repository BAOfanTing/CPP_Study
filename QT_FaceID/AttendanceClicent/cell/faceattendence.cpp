#include "faceattendence.h"
#include "ui_faceattendence.h"

FaceAttendence::FaceAttendence(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FaceAttendence)
{
    ui->setupUi(this);

    //打开摄像头
    cap.open(0);//如果是linux的话，dev/video
    //启动定时器，每多少毫秒采集一次
    startTimer(100);

    //导入级联分类器
    cascade.load("E:/Environment/opencv452/etc/haarcascades/haarcascade_frontalface_alt2.xml");

    //QTcpSocket当断开连接的时候disconnected信号，连接成功会发送connected
    connect(&m_socket,&QTcpSocket::disconnected,this,&FaceAttendence::start_connect);
    connect(&m_socket,&QTcpSocket::connected,this,&FaceAttendence::stop_connnect);

    //定时器到时间，连接服务器
    connect(&m_timer,&QTimer::timeout,this,&FaceAttendence::timer_connect);
    //启动定时器,每5s连接一次直到成功
    m_timer.start(5000);
}

FaceAttendence::~FaceAttendence()
{
    delete ui;
}

void FaceAttendence::timerEvent(QTimerEvent *e)
{
    //采集数据
    Mat srcImage;
    if(cap.grab())
    {
        cap.read(srcImage);
        // 水平镜像图像
        cv::flip(srcImage, srcImage, 1);
    }
    //把图像转为灰度图，提高处理速度
    Mat grayImage;
    cvtColor(srcImage,grayImage,COLOR_BGR2GRAY);

    //检测人脸
    std::vector<Rect> faceRects;
    cascade.detectMultiScale(grayImage,faceRects,1.1,3);
    if(faceRects.size()>0)
    {
        Rect rect = faceRects.at(0);//第一个人脸的矩形框
        //绘制矩形框
        // rectangle(srcImage,rect,Scalar(0,0,255));

        //移动圆形检测框
        ui->lb_traceFace->move(rect.x-rect.width/2,rect.y-rect.height/2);
    }
    else
    {
        //没有检测到人脸 移动圆形检测框到中心
        ui->lb_traceFace->move(100,60);
    }

    //没有数据返回
    if(srcImage.data == NULL)
    {
        return;
    }
    // 将 OpenCV 的 Mat 格式（BGR）转换为 Qt 的 QImage 格式（RGB）
    cvtColor(srcImage, srcImage, COLOR_BGRA2RGB);

    // 将 Mat 数据转换为 QImage
    QImage image(srcImage.data, srcImage.cols, srcImage.rows, srcImage.step1(), QImage::Format_RGB888);

    // 将 QImage 转换为 QPixmap
    QPixmap mmp = QPixmap::fromImage(image);

    // 将 QPixmap 显示在 QLabel 控件上
    ui->lb_camera->setPixmap(mmp);
}


void FaceAttendence::timer_connect()
{
    //连接服务器
    m_socket.connectToHost("ip地址",22);
}

void FaceAttendence::stop_connnect()
{
    //停止计时器
    m_timer.stop();
    QMessageBox::information(nullptr,"信息","连接成功");
}

void FaceAttendence::start_connect()
{
    //5秒连接
    m_timer.start(5000);
    QMessageBox::information(nullptr,"信息","服务器断开");
}
