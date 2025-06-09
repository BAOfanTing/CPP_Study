#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QImage>
#include <QtDebug>
#include "mygraphicsview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void sig_DrawRect(bool bDraw);
    void sig_DrawLine(bool bDraw);
    void sig_DrawPoint(bool bDraw);
    void sig_DrawIndex(int index);
    void sig_CanScale(int value);
    void sig_ShowImage();

private slots:
    void on_btn_Rect_clicked();

    void on_btn_Line_clicked();


    void on_btn_SelectImg_clicked();

    void on_btn_Point_clicked();

    void on_btn_Clear_clicked();
	void on_btn_Save_clicked();

    void on_cb_item_activated(int index);

    void on_btn_scale_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    MyGraphicsView *gv_view;


};
#endif // MAINWINDOW_H
