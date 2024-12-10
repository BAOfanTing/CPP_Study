#ifndef TIMERTHREAD_H
#define TIMERTHREAD_H

#include <QObject>
#include <QTimer>
#include <QThread>
#include <cmath>
#include <QDebug>


/******************************************************************************
 *
 * @file       timerthread.h
 * @brief      把计时放入线程
 *
 * @author     纯真丁一郎
 * @date       2024/09/18
 * @Blog       https://www.relxdingyilang.cn/
 * @history
 *****************************************************************************/

class TimerThread : public QObject
{
    Q_OBJECT
public:
    explicit TimerThread(QObject *parent = nullptr);

    //判断运行状态
    bool isRunning = false;

    QString caculateTime(int totaltime);

    void getid();

signals:
    void timeUpdated(QString totaltimestr); //发送时间给主界面
    void sig_isRunning(bool isRunning);//发送状态

public slots:

    void start();
    void stop();
    void pause();
    void onTimeout();

private:
    int m_totaltime; //总时间
    QTimer *timer;
};

#endif // TIMERTHREAD_H
