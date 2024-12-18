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
        {Qt::UserRole+6,"fileName"},
        {Qt::UserRole+7,"fileSize"},
        {Qt::UserRole+8,"filePath"},
        {Qt::UserRole+9,"fileSuffix"}, //后缀
        //文本
        {Qt::UserRole+100,"text"},
        //图片
        {Qt::UserRole+200,"imagePath"},

    };
}

QVariant TalkListModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()){
        return QVariant();
    }
    //增加下标越界判断
    const int row = index.row();
    if(row <0 && row > talkList.size())
    {
        return 0;
    }
    auto item = talkList.at(row);

    switch(role)
    {
        case Qt::UserRole+0:
            return item->id;
        case Qt::UserRole+1:
            return item->user;
        case Qt::UserRole+2:
            return item->sender;
        case Qt::UserRole+3:
            return QDateTime::fromSecsSinceEpoch(item->datetime).toString("hh:mm");
        case Qt::UserRole+4:
            return item->type;
        case Qt::UserRole+5:
            return item->status;
        case Qt::UserRole+6:
            return item->fileName;
        case Qt::UserRole+7:
            return item->fileSize;
        case Qt::UserRole+8:
            return item->filePath;
        case Qt::UserRole+9:
            return item->fileSuffix;
        case Qt::UserRole+100:
        {
            //文本
            TalkDataText *talk_text = static_cast<TalkDataText*>(item.get());
            return talk_text->text;
        }
        case Qt::UserRole+200:
        {
            //图片
            TalkDataImage *talk_image = static_cast<TalkDataImage*>(item.get());
            return talk_image->imagePath;
        }
        default:
            break;
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
    talk_data->datetime = caculateTime();
    talk_data->type = TalkData::Text;
    talk_data->status = TalkData::ParseSuccess;
    talk_data->text = text;

    //插入模型
    beginInsertRows(QModelIndex(),talkList.count(),talkList.count());
    talkList.push_back(QSharedPointer<TalkDataBasic>(talk_data));
    endInsertRows();

}

//图片消息
void TalkListModel::appendImage(const QString &user, const QString &sender, const QString &ImageUrl)
{
    TalkDataImage *talk_data = new TalkDataImage;
    talk_data->id = 0;
    talk_data->user = user;
    talk_data->sender = sender;
    talk_data->datetime = caculateTime();
    talk_data->type = TalkData::Image;
    talk_data->status = TalkData::ParseSuccess;
    talk_data->imagePath = ImageUrl;

    //插入模型
    beginInsertRows(QModelIndex(),talkList.count(),talkList.count());
    talkList.push_back(QSharedPointer<TalkDataBasic>(talk_data));
    endInsertRows();

}

void TalkListModel::appendOtherFile(const QString &user, const QString &sender, const QString &filePath, const QString &fileName, const QString &fileSize, const QString &fileSuffix)
{
    TalkDataOtherFile *talk_data = new TalkDataOtherFile;
    talk_data->id = 0;
    talk_data->user = user;
    talk_data->sender = sender;
    talk_data->datetime = caculateTime();
    talk_data->type = TalkData::Other;
    talk_data->status = TalkData::ParseSuccess;
    talk_data->filePath = filePath;
    talk_data->fileSize = fileSize;
    talk_data->fileName = fileName;
    talk_data->fileSuffix = fileSuffix;

    // // 打印输出
    // qDebug() << "File Path: " <<  talk_data->filePath;
    // qDebug() << "File Name: " << talk_data->fileName;
    // qDebug() << "File Size: " << talk_data->fileSize ;
    // qDebug() << "File Suffix: " << talk_data->fileSuffix;

    //插入模型
    beginInsertRows(QModelIndex(),talkList.count(),talkList.count());
    talkList.push_back(QSharedPointer<TalkDataBasic>(talk_data));
    endInsertRows();

}

void TalkListModel::controlDisplayMessagesCount()
{
    //超出消息上限,移除第一条消息
    if(talkList.size() >= nDisplayMessages)
    {
        beginRemoveRows(QModelIndex(),0,0);
        talkList.removeFirst();
        endRemoveRows();
    }
}

qint64 TalkListModel::caculateTime()
{
    qint64 currentTime = QDateTime::currentSecsSinceEpoch();
    //记录首次时间
    if(lastShowTime == 0)
    {
        lastShowTime = currentTime;
        return lastShowTime;
    }
    else //计算时差重置最后时间
    {
        QDateTime lastDateTime = QDateTime::fromSecsSinceEpoch(lastShowTime);
        QDateTime currentDateTime = QDateTime::fromSecsSinceEpoch(currentTime);

        //计算时差,转换为差了几秒
        qint64 timeDiff = lastDateTime.secsTo(currentDateTime);

        timeDiff = timeDiff / 30; //转换为分钟

        // qDebug() << "timeDiff" << timeDiff;
        if(timeDiff >= 1 )
        {
            lastShowTime = QDateTime::currentSecsSinceEpoch();
            return lastShowTime;
        }
        return 0;
    }
}

