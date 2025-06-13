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

    if(!m_logFile.open(QIODevice::Append | QIODevice::Truncate | QIODevice::Text))
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


/***********************************************
 * @功能描述 : 接受主界面传入的textedit
 * @创建者   : 石桢楠
 * @创建时间 : 2025-06-13
 * @参数     : none
 * @返回值   : none
 ***********************************************/
void LogItem::setlogWidget(QTextEdit * logTextEdit)
{
	m_pteLog = logTextEdit;
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
      qDebug()<<timeAndMessage;
      m_textStream.flush();

	  //输出日志到界面
	  if (m_pteLog)
	  {
		  m_pteLog->append(timeAndMessage);
	  }
    }

}

