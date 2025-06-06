#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>

class MainWindow;  // 前向声明

class MyGraphicsView :public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyGraphicsView(MainWindow *window,QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;


public slots:
    void showImage();

private:
    MainWindow *m_window;
    bool m_bDrawRect = false;
    bool m_bDrawPoint = false;
    bool m_bDrawLine = false;
    int m_bCanScale = 0;

};

#endif // MYGRAPHICSVIEW_H
