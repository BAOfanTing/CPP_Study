#include "talklistmodel.h"

TalkListModel* TalkListModel::instance = nullptr;

TalkListModel::TalkListModel()
{

}

TalkListModel *TalkListModel::getInstance()
{
    if(instance == nullptr)
    {
        instance = new TalkListModel();
    }
    return instance;
}

int TalkListModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid()){
        return 0;
    }
    return talkList.count();

}
QHash<int, QByteArray> TalkListModel::roleNames() const
{
    return QHash<int,QByteArray>{
        //基本信息
        {Qt::UserRole+0,"id"},
        {Qt::UserRole+1,"user"},
        {Qt::UserRole+2,"sender"},
        {Qt::UserRole+3,"datetime"},
        {Qt::UserRole+4,"type"},
        {Qt::UserRole+5,"status"},
        //文本
        {Qt::UserRole+100,"text"}
    };
}

QVariant TalkListModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()){
        return QVariant();
    }
    const int row = index.row();
    auto item = talkList.at(row);

    switch(role)
    {
        default:
            break;
        case Qt::UserRole+0:
            return item->id;
        case Qt::UserRole+1:
            return item->user;
        case Qt::UserRole+2:
            return item->sender;
        case Qt::UserRole+3:
            return QDateTime::fromSecsSinceEpoch(item->datetime).toString("yyyy-MM-dd hh:mm");
        case Qt::UserRole+4:
            return item->type;
        case Qt::UserRole+5:
            return item->status;
        case Qt::UserRole+100:
        {
            //文本
            TalkDataText *talk_text = static_cast<TalkDataText*>(item.get());
            return talk_text->text;
        }
    }
}

void TalkListModel::clearModel()
{
    beginResetModel();
    talkList.clear();
    endResetModel();
}

void TalkListModel::appendText(const QString &user, const QString &sender, const QString &text)
{
    TalkDataText *talk_data = new TalkDataText;
    talk_data->id = 0;
    talk_data->user = user;
    talk_data->sender = sender;
    talk_data->datetime = QDateTime::currentSecsSinceEpoch();
    talk_data->type = TalkData::Text;
    talk_data->status = TalkData::ParseSuccess;
    talk_data->text = text;

    //插入模型
    beginInsertRows(QModelIndex(),talkList.count(),talkList.count());
    talkList.push_back(QSharedPointer<TalkDataBasic>(talk_data));
    endInsertRows();
}

