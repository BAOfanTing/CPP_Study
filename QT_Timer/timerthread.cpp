#include "timerthread.h"

TimerThread::TimerThread(QObject *parent)
    : QObject{parent}
{
    m_totaltime = 0;
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&TimerThread::onTimeout);

}

void TimerThread::start(){
    timer->start(1);
    isRunning = true;
    emit sig_isRunning(isRunning);

}

void TimerThread::pause(){
    timer->stop();
    isRunning = false;
    emit sig_isRunning(isRunning);
}

void TimerThread::stop(){
    timer->stop();
    isRunning = false;
    m_totaltime = 0;
    emit sig_isRunning(isRunning);
}

void TimerThread::onTimeout(){
    //计时
    m_totaltime += 1;
    emit timeUpdated(caculateTime(m_totaltime));
    // this->getid();
}

QString TimerThread::caculateTime(int totaltime){
    //格式化字符串
    int millisecond =totaltime % 1000;
    millisecond = std::floor(millisecond/10);
    int second = int(std::floor(totaltime /1000) )% 60;
    int minute = int(std::floor(totaltime/1000 /60)) % 60;

    QString result = (minute<10 ? "0":"") + QString::number(minute)+":"+
                     (second<10 ? "0":"") + QString::number(second) + ":"+
                     (millisecond<10 ? "0":"")+QString::number(millisecond);

    return result;
}

void TimerThread::getid(){
    qDebug() <<"定时器线程ID: "<< QThread::currentThreadId();
}
