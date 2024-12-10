#ifndef TALKLISTMODEL_H
#define TALKLISTMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <QSharedPointer>
#include "TalkListDefine.h"
#include <QDateTime>

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

private:
    //私有化构造
    TalkListModel();
    //禁止复制构造和赋值操作
    TalkListModel(const TalkListModel&) = delete;
    TalkListModel &operator = (const TalkListModel&) = delete;

    //静态实例
    static TalkListModel *instance;

    QList<QSharedPointer<TalkDataBasic>> talkList;
};

#endif // TALKLISTMODEL_H
