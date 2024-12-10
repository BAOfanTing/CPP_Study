#ifndef ATTENDANCEWINDOW_H
#define ATTENDANCEWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>
#include "lib/qfaceobject.h"
#include <opencv.hpp>
#include <QSqlTableModel>>
#include <QSqlQuery>
#include <QSqlRecord>
#include "cell/register_ui.h"
using namespace cv;


QT_BEGIN_NAMESPACE
namespace Ui {
class AttendanceWindow;
}
QT_END_NAMESPACE

class AttendanceWindow : public QMainWindow
{
    Q_OBJECT

public:
    AttendanceWindow(QWidget *parent = nullptr);
    ~AttendanceWindow();

public slots:

    // 接受客户端连接的槽函数
    void accept_client();
    // 读取数据的槽函数
    void read_data();

private slots:
    void on_btn_register_clicked();

private:
    Ui::AttendanceWindow *ui;

    // TCP服务器对象
    QTcpServer m_server;

    // 与客户端通信的套接字对象
    QTcpSocket *m_socket;

    qint64 bsize;

    QFaceObject m_faceobject;
    //定义数据库表格模型
    QSqlTableModel model;

    //测试功能
    register_ui ww;
};
#endif // ATTENDANCEWINDOW_H
