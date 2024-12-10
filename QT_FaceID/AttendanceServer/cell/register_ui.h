#ifndef REGISTER_UI_H
#define REGISTER_UI_H

#include <QWidget>
#include <QFileDialog>
#include <QSqlTableModel>
#include <QSqlRecord>
#include "lib/qfaceobject.h"
#include <QMessageBox>
#include <opencv.hpp>
#include <QDir>


using namespace cv;

namespace Ui {
class register_ui;
}

class register_ui : public QWidget
{
    Q_OBJECT

public:
    explicit register_ui(QWidget *parent = nullptr);
    ~register_ui();

    //定时器事件
    void timerEvent(QTimerEvent *e);

private slots:
    // 点击“清除”按钮的槽函数
    void on_btn_clear_clicked();

    // 点击“添加头像”按钮的槽函数
    void on_btn_addhead_clicked();

    // 点击“注册”按钮的槽函数
    void on_btn_register_clicked();

    // 点击“打开摄像头”按钮的槽函数
    void on_btn_opencamera_clicked();

    void on_btn_shoot_clicked();

private:
    Ui::register_ui *ui;  // Qt 设计器生成的 UI 类指针

    int timerID;  // 定时器 ID

    // OpenCV 的视频捕获对象，用于访问摄像头
    cv::VideoCapture cap;

    cv::Mat srcImage;
};

#endif // REGISTER_UI_H
