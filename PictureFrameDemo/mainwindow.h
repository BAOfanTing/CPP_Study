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
    void on_m_prbtnRect_clicked();
    void on_m_prbtnLine_clicked();
    void on_m_ppbtnSelectImage_clicked();
    void on_m_prbtnPoint_clicked();
    void on_m_ppbtnClear_clicked();
	void on_m_ppbtnSaveImage_clicked();
    void on_m_pcbxSelectItem_activated(int index);
	void on_m_pactShowLog_changed();

private:
    Ui::MainWindow *ui; 
    MyGraphicsView *m_pgvView; 
};
#endif // MAINWINDOW_H
