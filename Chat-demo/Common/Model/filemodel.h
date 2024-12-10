#ifndef FILEMODEL_H
#define FILEMODEL_H

#include <QObject>
#include <QFileDialog>
#include <QUrl>
#include <QDebug>
#include <QFileInfo>
struct FileInfo {
    QString fileSizeStr;
    QString fileName;
    QString fileSuffix;
};

class FileModel : public QObject
{
    Q_OBJECT
public:
    static FileModel *getInstance();

    //获取选择的文件路径
    Q_INVOKABLE QUrl getSelectedFileUrl();

    //获取文件信息
    Q_INVOKABLE QVariant extractFileInfo(const QString &filePath);
    //格式化文件大小
    QString formatFileSize(qint64 size);

    //获取表情模型
    Q_INVOKABLE QStringList getEmojiName();

private:
    //私有化构造
    FileModel();
    //禁止复制构造和赋值操作
    FileModel(const FileModel&) = delete;
    FileModel &operator = (const FileModel&) = delete;
    static FileModel *instance;     //静态实例

signals:
};

#endif // FILEMODEL_H
