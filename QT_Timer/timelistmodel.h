#ifndef TIMELISTMODEL_H
#define TIMELISTMODEL_H

#include <QAbstractListModel>

// TimeListModel 类继承自 QAbstractListModel，用于管理和显示一个时间列表数据模型
class TimeListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TimeListModel(QObject *parent = nullptr);

    // 返回模型中数据的总数，用于 ListView 获取到数据的数量
    // 这个函数是 QAbstractListModel 的纯虚函数，必须实现
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    // 返回模型的角色名称，用于在 QML 中根据角色访问数据
    // 例如，NumberRole 对应的别名可以被 ListView 使用
    virtual QHash<int, QByteArray> roleNames() const override;

    // 获取指定行和角色的数据，这个函数会在 ListView 渲染数据时被调用
    // 数据是从 QList 中的 Data 结构体获取的
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Q_INVOKABLE 使得这些方法可以从 QML 中被调用
    // append 函数用于向模型中添加数据，接收 idnumber 和 timeStr 两个字符串
    Q_INVOKABLE void append(const QString &idnumber , const QString &timeStr);

    // 清空模型中的所有数据
    Q_INVOKABLE void clear();

private:
    // 定义一个结构体来存储列表项的数据，包括 idnumber 和 timeStr
    struct Data{
        QString m_idnumber; // 存储编号
        QString m_timeStr;  // 存储时间字符串
    };

    // 使用 QList 来存储所有 Data 结构体的数据
    QList<Data> m_datalist;

    // 枚举角色，用于指定 QML 中访问数据的键值
    // NumberRole 和 TimerRole 允许 QML 中根据不同的键来访问数据
    enum DataRoles{
        NumberRole = Qt::UserRole + 1, // 用户自定义的角色从 Qt::UserRole 开始
        TimerRole,                     // 时间角色
    };
};

#endif // TIMELISTMODEL_H
