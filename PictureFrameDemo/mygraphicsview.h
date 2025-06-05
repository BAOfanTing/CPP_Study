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

public slots:


private:
    MainWindow *m_window;
    bool m_bDrawRect = false;
    bool m_bDrawPoint = false;
    bool m_bDrawLine = false;

};

#endif // MYGRAPHICSVIEW_H
