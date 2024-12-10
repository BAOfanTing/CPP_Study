#ifndef FACEATTENDENCE_H
#define FACEATTENDENCE_H

#include <QMainWindow>
#include <opencv.hpp>

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

private:
    Ui::FaceAttendence *ui;

    //摄像头
    VideoCapture cap;

    //haar -- 级联分类器
    cv::CascadeClassifier cascade;
};
#endif // FACEATTENDENCE_H
