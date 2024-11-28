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
    TalkListModel();

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
    QList<QSharedPointer<TalkDataBasic>> talkList;
};

#endif // TALKLISTMODEL_H
