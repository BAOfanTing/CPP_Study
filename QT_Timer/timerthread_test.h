#ifndef TIMERTHREAD_TEST_H
#define TIMERTHREAD_TEST_H

#include <QThread>
#include <QTimer>
#include <cmath>
#include <QDebug>
class TimerThread_test : public QThread
{
    Q_OBJECT
public:
    explicit TimerThread_test(QObject *parent = nullptr);
    //判断运行状态
    bool isRunning = false;
    void getid();
    Q_INVOKABLE void initThread();
    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void onTimeout();

signals:
    void timeUpdated(QString totaltimestr); //发送时间给主界面
    void sig_isRunning(bool isRunning);//发送状态

public slots:



private:
    QThread *m_thread;
    TimerThread_test * m_worker;
    int m_totaltime; //总时间
    QTimer *timer;
};


#endif // TIMERTHREAD_TEST_H
