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
    QUrl filePath = QFileDialog::getOpenFileUrl(
        nullptr,
        QString("选择文件"),                            //标题
        QUrl(),                                     //默认路径
        QString("所有文件 (*);;文本文件 (*.txt)"),      //筛选格式
        nullptr,
        QFileDialog::DontUseNativeDialog            //不使用官方样式,自定义
        );    //过滤文件
    return filePath;
}


