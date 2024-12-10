#include "timerthread_test2.h"

// TimerThread_test2::TimerThread_test2(QString &timeStr): m_timeStr(timeStr)
TimerThread_test2::TimerThread_test2(QObject *parent) : QObject(parent)
{
    m_totaltime = 0;
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&TimerThread_test2::onTimeout);
}

void TimerThread_test2::start(){
    timer->start(1);
    isRunning = true;
    emit sig_isRunning(isRunning);
    //qDebug()<< "TimerThread_test2: start";
    getid();
}

void TimerThread_test2::pause(){
    timer->stop();
    isRunning = false;
    emit sig_isRunning(isRunning);
}

void TimerThread_test2::stop(){
    timer->stop();
    isRunning = false;
    m_totaltime = 0;
    emit sig_isRunning(isRunning);
}

void TimerThread_test2::onTimeout(){
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
    emit timeUpdated(result);
}
void TimerThread_test2::getid(){
    qDebug() <<"定时器线程ID: "<< QThread::currentThreadId();
}



// TimerInterface::TimerInterface() : m_TimerThread_test2(m_timeStr)
TimerInterface::TimerInterface(QObject *parent) : QObject(parent)
{
    m_TimerThread_test2.moveToThread(&m_Thread);
    connect(this,&TimerInterface::sig_start,&m_TimerThread_test2,&TimerThread_test2::start);
    connect(this,&TimerInterface::sig_pause,&m_TimerThread_test2,&TimerThread_test2::pause);
    connect(this,&TimerInterface::sig_stop,&m_TimerThread_test2,&TimerThread_test2::stop);
    connect(&m_TimerThread_test2,&TimerThread_test2::timeUpdated,this, &TimerInterface::get_Updated);
    connect(&m_TimerThread_test2,&TimerThread_test2::sig_isRunning,this,&TimerInterface::get_is_Running);
    m_Thread.start();
}

TimerInterface::~TimerInterface()
{
    m_Thread.quit();
    m_Thread.wait();
}

void TimerInterface::start()
{
    emit sig_start();
    qDebug() << "TimerInterface start in  : " << QThread::currentThreadId();
}

void TimerInterface::pause()
{
    emit sig_pause();
}

void TimerInterface::stop()
{
    emit sig_stop();
}

void TimerInterface::get_is_Running(bool is_running)
{
    sig_isRunning(is_running);
}

void TimerInterface::get_Updated(QString timeStr)
{
    emit sig_timeUpdated(timeStr);
}

