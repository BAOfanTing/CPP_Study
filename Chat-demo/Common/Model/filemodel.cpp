#include "filemodel.h"

//一开始需要置空,类外赋值
FileModel* FileModel::instance = nullptr;
FileModel::FileModel()
{

}

FileModel *FileModel::getInstance()
{
    if(instance == nullptr)
    {
        instance = new FileModel();
    }
    return instance;
}

QUrl FileModel::getSelectedFileUrl()
{
    QUrl filePath =QFileDialog::getOpenFileUrl(
        nullptr,
        QString("选择文件"),                            //标题
        QUrl(),                                     //默认路径
        QString("所有文件 (*);;文本文件 (*.txt)"),      //筛选格式
        nullptr,
        QFileDialog::DontUseNativeDialog            //不使用官方样式,自定义
        );    //过滤文件
    return filePath;
}

QVariant FileModel::extractFileInfo(const QString &filePath)
{
    QUrl url(filePath);
    QString localPath = url.toLocalFile(); //将qml路径转换为本地路径

    QFileInfo fileInfo(localPath);
    // 获取文件的大小、文件名和文件后缀
    qint64 fileSize = fileInfo.size();
    QString fileName = fileInfo.fileName();    // 文件名 + 后缀
    QString fileSuffix = fileInfo.suffix();    // 文件后缀（如：jpeg）
    QString fileSizeStr = formatFileSize(fileSize);

    // 打印输出
    // qDebug() << "File Path: " << localPath;
    // qDebug() << "File Name: " << fileName;
    // qDebug() << "File Size: " << fileSize ;
    // qDebug() << "File Suffix: " << fileSuffix;

    QVariantMap map; //把数据变成qml能够接受的格式
    map["fileName"] = fileName;
    map["fileSize"] = fileSizeStr;
    map["fileSuffix"] = fileSuffix;
    return map;
}

QString FileModel::formatFileSize(qint64 size)
{
    if (size < 1024)
    {
        return QString::number(size) + " B";
    }
    else if (size < 1024 * 1024)
    {
        return QString::number(size / 1024.0, 'f', 2) + " KB";
    }
    else if (size < 1024 * 1024 * 1024)
    {
        return QString::number(size / (1024.0 * 1024), 'f', 2) + " MB";
    }
    else
    {
        return QString::number(size / (1024.0 * 1024 * 1024), 'f', 2) + " GB";
    }
}

QStringList FileModel::getEmojiName()
{
    QDir dir("E:/QTproject/CPP_Study/Chat-demo/InstantMessage/icon/emoji");//表情所在地址,使用绝对地址
    if(!dir.exists())
    {
        qDebug()<< "表情包路径不存在";
    }
    QStringList files = dir.entryList(QDir::Files | QDir::NoDotAndDotDot);
    return files;
}



