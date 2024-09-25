#ifndef TIMERTHREAD_TEST2_H
#define TIMERTHREAD_TEST2_H

#include <QObject>
#include <QTimer>
#include <QThread>
#include <cmath>
#include <QDebug>

class TimerThread_test2 : public QObject
{
    Q_OBJECT
public:
    // explicit TimerThread_test2(QString &timeStr);
    explicit TimerThread_test2(QObject *parent = nullptr);
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
    QString m_timeStr;
};


class TimerInterface: public QObject{
    Q_OBJECT
    // Q_PROPERTY(QString timeStr READ getData NOTIFY dataChanged)
public:
    explicit TimerInterface(QObject *parent = nullptr);
    ~TimerInterface();
    Q_INVOKABLE void start();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void stop();

    void get_is_Running(bool is_running);
    void get_Updated(QString timeStr);
signals:
    void sig_start();
    void sig_stop();
    void sig_pause();
    void sig_isRunning(bool is_running);
    void sig_timeUpdated(QString timeStr);
private:
    QThread m_Thread;
    QString m_timeStr;
    TimerThread_test2 m_TimerThread_test2;
};

#endif // TIMERTHREAD_TEST2_H
