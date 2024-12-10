#include "attendancewindow.h"
#include "ui_attendancewindow.h"

AttendanceWindow::AttendanceWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AttendanceWindow)
{
    ui->setupUi(this);

    // 当有客户端连接时，触发 newConnection 信号
    // 并将其连接到 accept_client 槽函数
    connect(&m_server,&QTcpServer::newConnection,this,&AttendanceWindow::accept_client);
    // 监听指定的IP地址和端口，启动TCP服务器
    m_server.listen(QHostAddress::Any,9999);
}

AttendanceWindow::~AttendanceWindow()
{
    delete ui;
}

void AttendanceWindow::accept_client()
{
    //获取与客户端通信的套接字
    m_socket = m_server.nextPendingConnection();
    // 当套接字准备好读取数据时，触发 readyRead 信号
    // 并将其连接到 read_data 槽函数
    connect(m_socket,&QTcpSocket::readyRead,this,&AttendanceWindow::read_data);
}

void AttendanceWindow::read_data()
{
    // 从套接字中读取所有数据
    QString msg = m_socket->readAll();
    qDebug()<<msg;
}
