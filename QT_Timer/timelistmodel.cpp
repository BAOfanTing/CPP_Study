#include "timelistmodel.h"

// 构造函数，初始化父对象，列表模型没有其他特殊初始化
TimeListModel::TimeListModel(QObject *parent)
    : QAbstractListModel{parent}
{}

// 返回列表项的数量，用于 ListView 知道有多少项要显示
int TimeListModel::rowCount(const QModelIndex &parent) const
{
    // 返回数据列表的大小
    return m_datalist.size();
}

// 定义数据角色的名称映射，用于在 QML 中使用这些角色名称来访问数据
QHash<int, QByteArray> TimeListModel::roleNames() const
{
    // 设置角色与对应的名称，这样可以在 QML 中通过 "m_idnumber" 和 "m_timeStr" 获取对应的数据
    QHash<int,QByteArray> roles;
    roles[NumberRole] = "m_idnumber"; // 角色 NumberRole 对应 m_idnumber
    roles[TimerRole] = "m_timeStr";   // 角色 TimerRole 对应 m_timeStr
    return roles;
}

// 获取指定索引行和角色的数据，用于 ListView 显示数据
QVariant TimeListModel::data(const QModelIndex &index, int role) const
{
    int row = index.row(); // 获取当前索引的行号

    // 检查索引是否有效，避免访问越界
    if(row < 0 || row >= m_datalist.count()) {
        return QVariant(); // 返回无效数据
    }

    // 获取当前行对应的数据
    const Data &data = m_datalist[row];

    // 根据传入的角色返回不同的数据
    switch(role) {
    case NumberRole:
        return data.m_idnumber;  // 返回编号数据
    case TimerRole:
        return data.m_timeStr;   // 返回时间字符串数据
    default:
        return QVariant();       // 返回空值
    }
}

// 向数据列表中添加一项新数据
void TimeListModel::append(const QString &idnumber, const QString &timeStr)
{
    // 通知视图模型即将插入一行新数据，索引 0 表示新数据会插入到列表的最前面
    emit beginInsertRows(QModelIndex(), 0, 0);

    // 使用 prepend 将新的 Data 结构体添加到列表的开头
    m_datalist.prepend({idnumber, timeStr});

    // 通知视图模型插入操作完成，ListView 会根据此信号刷新显示
    emit endInsertRows();
}

// 清除所有数据
void TimeListModel::clear()
{
    int row = m_datalist.count(); // 获取当前数据的行数

    // 只有当数据列表不为空时才执行清除操作
    if(row > 0) {
        // 通知视图模型即将移除所有行，范围从 0 到最后一行
        emit beginRemoveRows(QModelIndex(), 0, m_datalist.size() - 1);

        // 清空数据列表
        m_datalist.clear();

        // 通知视图模型移除操作完成
        emit endRemoveRows();
    } else {
        return; // 如果没有数据，直接返回
    }
}
