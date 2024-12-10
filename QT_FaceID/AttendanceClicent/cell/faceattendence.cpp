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

    //接受json数据槽函数连接
    connect(&m_socket,&QTcpSocket::readyRead,this,&FaceAttendence::receive_data);
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

    // 如果检测到人脸且 flag_onepersion 大于等于 0
    if(faceRects.size()>0 && flag_onepersion >=0)
    {
        Rect rect = faceRects.at(0);//第一个人脸的矩形框
        //绘制矩形框
        // rectangle(srcImage,rect,Scalar(0,0,255));

        //移动圆形检测框
        ui->lb_traceFace->move(rect.x-rect.width/2,rect.y-rect.height/2);

        // 如果 flag_onepersion 大于 2，表示连续检测到人脸
        if(flag_onepersion > 2)
        {
            //把Mat数据转化为QbyteArry,编码成jpg格式
            vector<uchar> buf;
            cv::imencode(".jpg",srcImage,buf);
            QByteArray byte((const char*)buf.data(),buf.size());

            // 获取数据大小
            quint64 backsize = byte.size();
            // 创建用于发送数据的 QByteArray 对象
            QByteArray sendData;

            // 创建 QDataStream 对象，用于将数据写入 sendData
            QDataStream stream(&sendData, QIODevice::WriteOnly);

            // 设置 QDataStream 的版本
            stream.setVersion(QDataStream::Qt_6_4);

            // 将数据大小和字节数据写入 sendData
            stream << backsize << byte;

            // 将数据发送给客户端
            m_socket.write(sendData);
            // 重置 flag_onepersion 为 -2，避免连续发送
            flag_onepersion = -2;
        }
        // 增加 flag_onepersion，用于计数连续检测到人脸的次数
        flag_onepersion++;
    }
    if(faceRects.size() == 0)
    {
        //没有检测到人脸 移动圆形检测框到中心
        ui->lb_traceFace->move(100,60);

         // 重置 flag_onepersion，重新开始计数
        flag_onepersion = 0;
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
    m_socket.connectToHost("192.168.1.8",8866);
    qDebug()<<"正在连接服务器";
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

// 接收数据槽函数
void FaceAttendence::receive_data()
{
    //{employeeID:%1, name : %2,address:%3,time:%4}
    // 接受数据并展示
    QByteArray array = m_socket.readAll(); // 读取所有接收到的数据

    // JSON解析
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(array, &err);

    // 检查JSON解析错误
    if (err.error != QJsonParseError::NoError)
    {
        qDebug() << "Json格式错误";
        return;
    }

    // 获取JSON对象
    QJsonObject obj = doc.object();

    // 获取员工ID、姓名、时间和地址信息
    QString employeeID = obj.value("employeeID").toString(); // 员工ID
    QString name = obj.value("name").toString();             // 姓名
    QString timestr = obj.value("time").toString();          // 时间字符串
    QString address = obj.value("address").toString();       // 地址

    // 更新界面显示
    ui->lb_employeeID->setText(employeeID);  // 员工ID标签
    ui->lb_nickname->setText(name);          // 姓名标签
    ui->lb_address->setText(address);        // 地址标签
    ui->lb_time->setText(timestr);           // 时间标签
}
