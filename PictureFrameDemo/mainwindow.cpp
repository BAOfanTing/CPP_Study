#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MyGraphicsView *gv_view = new MyGraphicsView(this);
    gv_view->setScene(new QGraphicsScene(this));  // 初始化视图场景
    // 放入垂直布局
    ui->verticalLayout_2->addWidget(gv_view);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_Rect_clicked()
{
    qDebug() << "按钮状态:" << ui->btn_Rect->isChecked();
    emit sig_DrawRect(ui->btn_Rect->isChecked());
    emit sig_DrawLine(ui->btn_Line->isChecked());
    emit sig_DrawPoint(ui->btn_Point->isChecked());

}

void MainWindow::on_btn_Line_clicked()
{
    qDebug() << "按钮状态:" << ui->btn_Line->isChecked();
    emit sig_DrawRect(ui->btn_Rect->isChecked());
    emit sig_DrawLine(ui->btn_Line->isChecked());
    emit sig_DrawPoint(ui->btn_Point->isChecked());

}

void MainWindow::on_btn_Point_clicked()
{
    qDebug() << "按钮状态:" << ui->btn_Point->isChecked();
    emit sig_DrawRect(ui->btn_Rect->isChecked());
    emit sig_DrawLine(ui->btn_Line->isChecked());
    emit sig_DrawPoint(ui->btn_Point->isChecked());
}

void MainWindow::on_btn_SelectImg_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("打开图片"), "",
                            tr("Image Files (*.png *.jpg *.jpeg *.bmp *.xpm)"));

    if (filename.isEmpty()) {
        return;
    }

    QImage image(filename);
    if (image.isNull()) {
        QMessageBox::warning(this, tr("错误"), tr("无法加载图片: %1").arg(filename));
        return;
    }
    QPixmap pixmap = QPixmap::fromImage(image);
    gv_view->scene()->addPixmap(pixmap);//添加图像到场景
}
