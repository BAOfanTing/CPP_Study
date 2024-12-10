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
    m_server.listen(QHostAddress::Any,8866);

    bsize = 0;
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
    // 创建 QDataStream 对象，并设置其版本为 Qt_6_4
    QDataStream stream(m_socket);
    stream.setVersion(QDataStream::Qt_6_4);

    // 如果 bsize 为零，则检查套接字中是否有足够的数据读取数据大小
    if (bsize == 0) {
        if (m_socket->bytesAvailable() < (qint64)sizeof(bsize)) {
            // 数据不足，返回
            return;
        }
        // 读取数据大小并将其赋予 bsize
        stream >> bsize;
    }

    // 检查套接字中是否有足够的数据读取图像数据
    if (m_socket->bytesAvailable() < bsize) {
        // 数据不足，返回
        return;
    }

    // 读取图像数据并将其赋予 data
    QByteArray data;
    stream >> data;

    // 将 bsize 重置为零
    bsize = 0;

    // 如果 data 为空，则返回
    if (data.size() == 0) {
        return;
    }
    // 使用 loadFromData() 函数从 data 中加载图像
    QPixmap m_mp;
    m_mp.loadFromData(data, "jpg");

    // 将图像缩放到 QLabel 控件的大小
    m_mp = m_mp.scaled(ui->lb_pic->size());

    // 将图像显示在 QLabel 控件上
    ui->lb_pic->setPixmap(m_mp);


    // 识别人脸
    // 定义一个 OpenCV 的 Mat 对象，用于存储人脸图像
    cv::Mat faceImage;

    // 定义一个无符号字符型向量 decode，用于存储解码后的数据
    std::vector<uchar> decode;

    // 调整 decode 的大小为与 data 相同
    decode.resize(data.size());

    // 将数据从 data 拷贝到 decode 中
    memcpy(decode.data(), data.data(), data.size());

    // 对解码后的数据进行颜色图像格式的解码，得到人脸图像
    faceImage = cv::imdecode(decode, cv::IMREAD_COLOR);

    // 使用 face_query 函数查询人脸，获取人脸ID
    int faceID = m_faceobject.face_query(faceImage);

    // 输出人脸ID信息
    qDebug() <<"face:::" <<faceID;
}

