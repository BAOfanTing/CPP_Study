#include "register_ui.h"
#include "ui_register_ui.h"

register_ui::register_ui(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::register_ui)
{
    ui->setupUi(this);
    //检查data文件夹是否存在
    QDir dir("./data/");
    if (!dir.exists())
    {
        dir.mkpath(".");
    }
}

register_ui::~register_ui()
{
    delete ui;
}

void register_ui::timerEvent(QTimerEvent *e)
{
    if(cap.isOpened()) // 如果摄像头成功打开
    {
        cap >> srcImage; // 从摄像头读取图像帧
        if(srcImage.data == nullptr) return; // 如果图像数据为空，则返回
    }

    // 将图像格式转换为Qt能够处理的格式
    cv::Mat outImage;
    cv::cvtColor(srcImage, outImage, cv::COLOR_BGR2RGB); // 将图像从BGR格式转换为RGB格式（OpenCV默认的颜色通道顺序与Qt不同）
    cv::flip(outImage, outImage, 1); // 水平翻转图像，因为摄像头的图像可能是镜像的

    QImage image(outImage.data, outImage.cols, outImage.rows, outImage.step1(), QImage::Format_RGB888); // 创建Qt的QImage对象

    // 在Qt界面上显示图像
    QPixmap mmp = QPixmap::fromImage(image); // 将QImage转换为QPixmap
    mmp = mmp.scaledToWidth(ui->lb_pic->width()); // 根据标签的宽度缩放图像
    ui->lb_pic->setPixmap(mmp); // 将图像显示在标签上
}

void register_ui::on_btn_clear_clicked()
{
    //重置内容
    ui->le_nickname->clear();
    ui->le_birthday->setDate(QDate::currentDate());
    ui->le_phone->clear();
    ui->le_adress->clear();
    ui->le_path->clear();
    ui->lb_pic->clear();
}

void register_ui::on_btn_addhead_clicked()
{
    //通过文件对话框选中文件
    QString filepath = QFileDialog::getOpenFileName(this);
    ui->le_path->setText(filepath);

    //显示图片,在图片标签中显示缩放后的图片
    QPixmap mmp(filepath);
    mmp = mmp.scaledToWidth(ui->lb_pic->width());
    // mmp = mmp.scaledToHeight(ui->lb_pic->height());
    ui->lb_pic->setPixmap(mmp);
    // // 设置图片在标签中居中显示
    // ui->lb_pic->setAlignment(Qt::AlignCenter);
}



void register_ui::on_btn_register_clicked()
{
    //1、通过照片，结合faceobject模块的到faceID
    QFaceObject faceobject;
    cv::Mat image = cv::imread(ui->le_path->text().toUtf8().data());
    int faceID = faceobject.face_register(image);
    //2、把个人信息储存到employee表
    QSqlTableModel model;
    model.setTable("employee");

    //把头像保存到一个路径下
    QString headfile = QString("./data/%1.jpg").arg((const QString&)ui->le_nickname->text().toUtf8().toBase64());
    cv::imwrite(headfile.toStdString(),image);
    QSqlRecord record = model.record();

     // 设置记录的各个字段值
    record.setValue("name",ui->le_nickname->text());
    record.setValue("sex",ui->btn_man->isChecked()?"男":"女");
    record.setValue("birthday",ui->le_birthday->text());
    record.setValue("address",ui->le_adress->text());
    record.setValue("phone",ui->le_phone->text());
    record.setValue("faceID",faceID);
    record.setValue("headfile",headfile);

    //3、提示注册成功
    // 插入记录到模型
    bool ret = model.insertRecord(0,record);
    if(ret)
    {
        // 提交所有的挂起的更改到数据库
        model.submitAll();
        QMessageBox::information(nullptr,"信息","注册成功");
    }
    else
    {
        QMessageBox::information(nullptr,"信息","注册失败，头像重复或信息错误");
    }
}


void register_ui::on_btn_opencamera_clicked()
{
    // 检查按钮文本，如果当前为“打开摄像头”
    if(ui->btn_opencamera->text() == "打开摄像头")
    {
        // 打开摄像头
        if(cap.open(0)) // 尝试打开摄像头设备（设备编号为0）
        {
            ui->btn_opencamera->setText("关闭摄像头"); // 设置按钮文本为“关闭摄像头”
            timerID = startTimer(100); // 启动定时器，以每100毫秒的间隔捕获摄像头图像
        }
    }
    else // 如果当前按钮文本不是“打开摄像头”，即为“关闭摄像头”
    {
        killTimer(timerID); // 停止定时器
        ui->btn_opencamera->setText("打开摄像头"); // 设置按钮文本为“打开摄像头”
        // 关闭摄像头
        cap.release(); // 释放摄像头资源
    }
}

void register_ui::on_btn_shoot_clicked()
{
    //保存数据
    if(ui->le_nickname->text() == "")
    {
        QMessageBox::information(nullptr,"信息","请先输入个人信息");
        return;
    }
    QString headfile = QString("./data/%1.jpg").arg((const QString&)ui->le_nickname->text().toUtf8().toBase64());
    ui->le_path->setText(headfile);
    cv::imwrite(headfile.toStdString(),srcImage);
    killTimer(timerID); // 停止定时器
    ui->btn_opencamera->setText("打开摄像头"); // 设置按钮文本为“打开摄像头”
    // 关闭摄像头
    cap.release(); // 释放摄像头资源
    QMessageBox::information(nullptr,"信息","拍照成功");
}

