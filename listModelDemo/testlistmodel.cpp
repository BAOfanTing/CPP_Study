#include "testlistmodel.h"
#include <QDebug>

testListModel::testListModel(QObject *parent)
    : QAbstractListModel{parent}
{
    initializeModel();
}

int testListModel::rowCount(const QModelIndex &parent) const
{
    return m_datalist.size();
}

QHash<int, QByteArray> testListModel::roleNames() const
{
    QHash<int,QByteArray> roles;
    roles[GroupRole] = "m_groupid";
    roles[MenberRole] = "m_members";
    return roles;
}

QVariant testListModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();

    if(row < 0 || row > m_datalist.count())
    {
        return QVariant();
    }
    const Data &data = m_datalist[row];

    switch(role){
    case GroupRole:
        return data.m_groupid;
    case MenberRole:
        return QVariant::fromValue(data.m_members);
    default:
        return QVariant();
    }
}

void testListModel::initializeModel()
{
    for (int i = 0; i < 12; ++i) { // 创建12个组
        Data data;
        data.m_groupid = i + 1; // 组ID从1开始

        for (int j = 0; j < 256; ++j) { // 每个组有35个成员
            data.m_members.append(j+ i + 1); // 成员ID从1开始
        }

        m_datalist.append(data);
    }
}

MemberListModel::MemberListModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

QHash<int, QByteArray> MemberListModel::roleNames() const
{
    QHash<int,QByteArray> roles;
    roles[MemberRole] = "m_members";
    roles[NameRole] = "m_name";
    return roles;
}

QVariant MemberListModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();

    if(row < 0 || row > m_members.count())
    {
        return QVariant();
    }
    const Member &data = m_members[row];

    switch(role){
    case MemberRole:
        return data.member;
    case NameRole:
        return data.name;
    default:
        return QVariant();
    }
}

void MemberListModel::setMembers(const QList<Member> &members)
{
    beginResetModel();
    m_members = members;
    endResetModel();
}
QVariant testListModel::getMemberModel(int index,int pageIndex,int pageSize) const
{
    // if (index < 0 || index >= m_datalist.size()) {
    //     return QVariant();
    // }
    // MemberListModel* model = new MemberListModel(m_datalist.at(index).m_members);
    // return QVariant::fromValue(model);

    int start = pageIndex * pageSize;
    int end = start +pageSize;
    end = qMin(end,256);
    start = qMax(start,0);
    qDebug() << index << pageIndex <<pageSize;
    QList<MemberListModel::Member> members;
    for(int i = start ;i<end; i++)
    {
        MemberListModel::Member member;
        member.member =(m_datalist.at(index).m_members[i]);
        member.name = QString("Member %1").arg(member.member);
        members.append(member);
    }

    MemberListModel* memberListModel = new MemberListModel();
    memberListModel->setMembers(members);
    return QVariant::fromValue(memberListModel);

}

