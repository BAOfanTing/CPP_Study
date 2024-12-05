#ifndef TALKLISTDEFINE_H
#define TALKLISTDEFINE_H

#include <QObject>
#include <QUrl>

//将枚举注册到QML
class TalkData : public QObject
{
    Q_OBJECT
public:
    using QObject::QObject;

    //数据类型
    enum DataType
    {
        Text,   //文本
        Image,  //图片
        Audio,  //语音
        Video,   //视频
        Other   //其他文件类型
    };
    Q_ENUM(DataType);

    //数据处理状态
    enum DataStatus
    {
        DataError,  //无效数据
        DataReady,  //代解析
        ParseOn,    //解析成功
        ParseSuccess,   //解析成功
        ParseError      //解析失败
    };
    Q_ENUM(DataStatus);
};

//消息基类
struct TalkDataBasic
{
    qint64 id;          //消息id
    QString user;       //消息所属用户
    QString sender;     //发送者
    qint64 datetime;    //发送时间 ms
    //消息类型:文本,语音,图片,视频
    TalkData::DataType type = TalkData::Text;
    //处理状态
    TalkData::DataStatus status = TalkData::DataError;
    QString fileName;   //名字
    QString fileSize;   //大小
    QString filePath;   //路径
    QString fileSuffix; //后缀
};

//文本消息
struct TalkDataText : public TalkDataBasic
{
    QString text;//文本信息
};

//图片消息
struct TalkDataImage : public TalkDataBasic
{
    QString imagePath;//图片路径
};

//其他发送文件消息
struct TalkDataOtherFile : public TalkDataBasic
{

};


#endif // TALKLISTDEFINE_H
