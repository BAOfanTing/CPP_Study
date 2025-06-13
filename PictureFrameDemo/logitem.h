#ifndef LOGITEM_H
#define LOGITEM_H
#include <QFile>
#include <QTextStream>
#include <QObject>
#include <QTextEdit>

class LogItem : public QObject
{
    Q_OBJECT
public:
    static LogItem *getInstance();

	void setlogWidget(QTextEdit *logTextEdit);
    void appendLog(const QString &message);


signals:


private:
     explicit LogItem(QObject *parent = nullptr);
    ~LogItem();
    void initLogFile();

    QFile m_logFile;
    static LogItem* m_instance;
     QTextStream m_textStream;

	 QTextEdit *m_pteLog = nullptr;

};

#endif // LOGITEM_H
