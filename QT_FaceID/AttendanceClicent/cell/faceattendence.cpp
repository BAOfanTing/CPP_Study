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
    startTimer(1);
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
