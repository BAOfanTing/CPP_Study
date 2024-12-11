#ifndef TALKLISTMODEL_H
#define TALKLISTMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <QSharedPointer>
#include "TalkListDefine.h"
#include <QDateTime>
#include <QDebug>

#define nDisplayMessages 10

class TalkListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    // 获取单例实例
    static TalkListModel* getInstance();

    //重写三个函数
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QHash<int,QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    //清空数据
    Q_INVOKABLE void clearModel();

    //发送文本
    Q_INVOKABLE void appendText(const QString &user,
                                const QString &sender,
                                const QString &text);
    //发送图片
    Q_INVOKABLE void appendImage(const QString &user,
                                 const QString &sender,
                                 const QString &ImageUrl);
    //发送其他文件
    Q_INVOKABLE void appendOtherFile(const QString &user,
                                     const QString &sender,
                                     const QString &filePath,
                                     const QString &fileName,
                                     const QString &fileSize,
                                     const QString &fileSuffix);

    //控制最大展示消息数量
    Q_INVOKABLE void controlDisplayMessagesCount();

    //计算时间间隔
    qint64 caculateTime();
private:
    //私有化构造
    TalkListModel();
    //禁止复制构造和赋值操作
    TalkListModel(const TalkListModel&) = delete;
    TalkListModel &operator = (const TalkListModel&) = delete;

    //静态实例
    static TalkListModel *instance;

    QList<QSharedPointer<TalkDataBasic>> talkList;

    qint64 lastShowTime = 0;
};

#endif // TALKLISTMODEL_H
