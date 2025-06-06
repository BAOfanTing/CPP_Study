#include "logitem.h"
#include <QDebug>
#include <QDateTime>

LogItem *LogItem::m_instance = new LogItem();

LogItem::LogItem(QObject *parent) : QObject(parent),m_logFile("./log.txt")
{
    initLogFile();
}
LogItem::~LogItem()
{
    if (m_logFile.isOpen())
    {
        m_logFile.close();
    }
}

//初始化
void LogItem::initLogFile()
{
    // 如果文件不存在，则创建空文件
    if (!QFile::exists(m_logFile.fileName()))
    {
        QFile newFile(m_logFile.fileName());
        if (!newFile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qWarning() << "无法创建日志文件:" << m_logFile.fileName();
            return;
        }
        newFile.close(); // 立即关闭（此时文件为空）
    }

    if(!m_logFile.open(QIODevice::Append | QIODevice::Text))
    {
        qWarning()<<"无法打开日志文件"<< m_logFile.fileName();
    }
    else
    {
        m_textStream.setDevice(&m_logFile);
        m_textStream.setCodec("UTF-8");
    }
}

LogItem *LogItem::getInstance()
{
    return m_instance;
}

//添加文本到日志文件
void LogItem::appendLog(const QString &message)
{
    if(!m_logFile.isOpen())
    {
        initLogFile();
    }
    QString timeAndMessage = QString("[%1] %2")
            .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"))
            .arg(message);

    if(m_textStream.device())
    {
      m_textStream << timeAndMessage <<"\n";
      m_textStream.flush();
    }

}

