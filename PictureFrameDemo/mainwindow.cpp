#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <logitem.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gv_view = new MyGraphicsView(this);
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
    LogItem::getInstance()->appendLog("框按下");
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
    if (!gv_view->scene()) {
        gv_view->setScene(new QGraphicsScene(this));
    } else {
        gv_view->scene()->clear();
    }
    //场景大小设置为视图大小
//    QRectF viewRect = gv_view->viewport()->rect();
//    gv_view->scene()->setSceneRect(0,0,viewRect.width(),viewRect.height());

    //缩放图片到场景大小
    QPixmap pixmap = QPixmap::fromImage(image);
    QSizeF targetsize = gv_view->scene()->sceneRect().size();
    QPixmap scaledPixmap = pixmap.scaled(targetsize.toSize(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    //将图片设置到场景
    gv_view->scene()->addPixmap(scaledPixmap);
    gv_view->setAlignment(Qt::AlignCenter);
}

void MainWindow::on_btn_Clear_clicked()
{
    //清空画的点线框
    for (auto item :  gv_view->scene()->items())
    {
        if (item->type() == QGraphicsRectItem::Type ||
            item->type() == QGraphicsLineItem::Type ||
            item->type() == QGraphicsEllipseItem::Type)
        {
             gv_view->scene()->removeItem(item);
        }
    }
}

void MainWindow::on_cb_item_activated(int index)
{
    emit sig_DrawIndex(index);
}

void MainWindow::on_btn_scale_stateChanged(int arg1)
{

}
