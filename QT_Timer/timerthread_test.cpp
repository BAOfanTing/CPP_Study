#include "timerthread_test.h"

TimerThread_test::TimerThread_test(QObject *parent)
    : QThread{parent}
{}

void TimerThread_test::initThread()
{
    m_thread = new QThread();
    m_worker = new TimerThread_test();

    m_worker->moveToThread(m_thread);
    m_thread->start();
    timer = new QTimer();

    connect(timer,&QTimer::timeout,this,&TimerThread_test::onTimeout);
}


void TimerThread_test::onTimeout(){
    //计时
    m_totaltime += 1;

    //格式化字符串
    int millisecond =m_totaltime % 1000;
    millisecond = std::floor(millisecond/10);
    int second = int(std::floor(m_totaltime /1000) )% 60;
    int minute = int(std::floor(m_totaltime/1000 /60)) % 60;

    QString result = (minute<10 ? "0":"") + QString::number(minute)+":"+
                     (second<10 ? "0":"") + QString::number(second) + ":"+
                     (millisecond<10 ? "0":"")+QString::number(millisecond);
    getid();
    emit timeUpdated(result);
    // this->getid();
}
void TimerThread_test::start(){
    timer->start(1);
    isRunning = true;
    emit sig_isRunning(isRunning);

}

void TimerThread_test::pause(){
    timer->stop();
    isRunning = false;
    emit sig_isRunning(isRunning);
}

void TimerThread_test::stop(){
    timer->stop();
    isRunning = false;
    m_totaltime = 0;
    emit sig_isRunning(isRunning);
}

void TimerThread_test::getid(){
    qDebug() <<"定时器线程ID: "<< QThread::currentThreadId();
}

