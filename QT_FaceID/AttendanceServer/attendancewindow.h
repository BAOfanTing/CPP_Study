#ifndef ATTENDANCEWINDOW_H
#define ATTENDANCEWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>


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

private:
    Ui::AttendanceWindow *ui;

    // TCP服务器对象
    QTcpServer m_server;

    // 与客户端通信的套接字对象
    QTcpSocket *m_socket;
};
#endif // ATTENDANCEWINDOW_H
