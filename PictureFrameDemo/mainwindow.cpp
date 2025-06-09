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
    gv_view = new MyGraphicsView(this);//获得场景实例
    // 放入垂直布局,MyGraphicsView只能够放入布局中
    ui->verticalLayout_2->addWidget(gv_view);
    //初始让按钮无法使用
    ui->btn_Line->setEnabled(false);
    ui->btn_Rect->setEnabled(false);
    ui->btn_Point->setEnabled(false);
    ui->btn_Clear->setEnabled(false);
    ui->cb_item->setEnabled(false);
    ui->btn_scale->setEnabled(false);
	ui->btn_Save->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_Rect_clicked()
{
    LogItem::getInstance()->appendLog(("框按下"));
    emit sig_DrawRect(ui->btn_Rect->isChecked());
    emit sig_DrawLine(ui->btn_Line->isChecked());
    emit sig_DrawPoint(ui->btn_Point->isChecked());
}

void MainWindow::on_btn_Line_clicked()
{
    LogItem::getInstance()->appendLog(("线按下"));
    emit sig_DrawRect(ui->btn_Rect->isChecked());
    emit sig_DrawLine(ui->btn_Line->isChecked());
    emit sig_DrawPoint(ui->btn_Point->isChecked());
}

void MainWindow::on_btn_Point_clicked()
{
    LogItem::getInstance()->appendLog(("点按下"));
    emit sig_DrawRect(ui->btn_Rect->isChecked());
    emit sig_DrawLine(ui->btn_Line->isChecked());
    emit sig_DrawPoint(ui->btn_Point->isChecked());
}

//保存图片和所有线框,缩放保存的也是原图
void MainWindow::on_btn_Save_clicked()
{
	LogItem::getInstance()->appendLog("保存图片");
	//使用文件选择的形式保存
	QString filePath = QFileDialog::getSaveFileName(this, tr("save image"), "",
		tr("PNG Images (*.png);;JPEG Images (*.jpg)"));

	if (filePath.isEmpty())
	{
		LogItem::getInstance()->appendLog("用户取消保存");
		return;
	}

	//获取场景
	QGraphicsScene *scene = gv_view->scene();
	QRectF sceneRect = scene->itemsBoundingRect(); //计算场景边界

	//生成图片
	QImage image(sceneRect.size().toSize(), QImage::Format_ARGB32);

	//使用render将场景渲染到painter
	QPainter painter(&image);
	scene->render(&painter, QRectF(QPoint(0, 0), sceneRect.size()), sceneRect);

	if (image.save(filePath))
	{
		LogItem::getInstance()->appendLog(tr("Image saved to %1").arg(filePath));
		QMessageBox::information(this, tr("information"), tr("Image Saved！"));
	}
	else
	{
		LogItem::getInstance()->appendLog(tr("Failed to save image."));
		QMessageBox::warning(this, tr("information"), tr("Image Saved Failed！"));
	}

}

//选择图片加载到场景
void MainWindow::on_btn_SelectImg_clicked()
{
    emit sig_ShowImage();
    //启用按钮
    ui->btn_Line->setEnabled(true);
    ui->btn_Rect->setEnabled(true);
    ui->btn_Point->setEnabled(true);
    ui->btn_Clear->setEnabled(true);
    ui->cb_item->setEnabled(true);
    ui->btn_scale->setEnabled(true);
	ui->btn_Save->setEnabled(true);
}

//清空画的点线框,不清空图片,若是想清空所有，直接调clear
void MainWindow::on_btn_Clear_clicked()
{
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

//combox的形式选择绘制那个图形
void MainWindow::on_cb_item_activated(int index)
{
    emit sig_DrawIndex(index);
}

//是否启用缩放
void MainWindow::on_btn_scale_stateChanged(int value)
{
    sig_CanScale(value);
    LogItem::getInstance()->appendLog(value >0 ? "场景缩放启动" : "场景缩放关闭" );
}
