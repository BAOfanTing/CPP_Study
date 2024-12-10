#ifndef TESTLISTMODEL_H
#define TESTLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>

class testListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit testListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    virtual QHash<int,QByteArray> roleNames() const override;

    QVariant data(const QModelIndex &index,int role = Qt::DisplayRole) const override;

    //初始化
    void initializeModel();

    // 新增方法：获取特定索引的 Data 对象
    Q_INVOKABLE QVariant  getMemberModel(int index,int pageIndex,int pageSize) const;
private:
    //定义结构体存储每页和数据
    struct Data{
        int m_groupid;
        QList<int> m_members;
    };

    //使用QList来存储所有的Data数据
    QList<Data> m_datalist;

    //枚举角色
    enum DataRoles{
        GroupRole = Qt::UserRole+1,
        MenberRole,
    };

signals:
};

class MemberListModel : public QAbstractListModel {
    Q_OBJECT
public:
    explicit MemberListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        return m_members.size();
    }
    virtual QHash<int,QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    struct Member
    {
        int member;
        QString name;
    };
    void setMembers(const QList<Member>& members);

private:

    QList<Member> m_members;
    //枚举角色
    enum DataRoles{
        MemberRole = Qt::UserRole+1,
        NameRole,
    };
};

#endif // TESTLISTMODEL_H
