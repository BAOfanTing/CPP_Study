#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QApplication>
#include "./Common/Model/TalkListDefine.h"
#include "./Common/Model/talklistmodel.h"
#include "./Common/Model/filemodel.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication app(argc, argv);


    qmlRegisterType<TalkData>("TalkModel",1,0,"TalkData");
    QQmlApplicationEngine engine;
    //获取单例
    TalkListModel* talkListModel = TalkListModel::getInstance();
    engine.rootContext()->setContextProperty("talkListModel",talkListModel);
    //文件单例
    FileModel* fileModel = FileModel::getInstance();
    engine.rootContext()->setContextProperty("fileModel",fileModel);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
