#ifndef LOGITEM_H
#define LOGITEM_H
#include <QFile>
#include <QTextStream>
#include <QObject>

class LogItem : public QObject
{
    Q_OBJECT
public:
    static LogItem *getInstance();

    void appendLog(const QString &message);


signals:


private:
     explicit LogItem(QObject *parent = nullptr);
    ~LogItem();
    void initLogFile();

    QFile m_logFile;
    static LogItem* m_instance;
     QTextStream m_textStream;

};

#endif // LOGITEM_H
