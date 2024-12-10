#ifndef FACEATTENDENCE_H
#define FACEATTENDENCE_H

#include <QMainWindow>
#include <opencv.hpp>
#include <QTcpSocket>
#include <QTimer>
#include <QMessageBox>>

using namespace cv;
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class FaceAttendence;
}
QT_END_NAMESPACE

class FaceAttendence : public QMainWindow
{
    Q_OBJECT

public:
    FaceAttendence(QWidget *parent = nullptr);
    ~FaceAttendence();

    //定时器事件
    void timerEvent(QTimerEvent *e);


public slots:
    void timer_connect();
    void stop_connnect();
    void start_connect();

private:
    Ui::FaceAttendence *ui;

    //摄像头
    VideoCapture cap;

    //haar -- 级联分类器
    cv::CascadeClassifier cascade;

    //创建网络前套字，定时器
    QTcpSocket m_socket;
    QTimer m_timer;
};
#endif // FACEATTENDENCE_H
