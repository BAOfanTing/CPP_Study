#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>
#include <QThread>
#include "timerthread.h"
#include <QQuickView>
#include <QQmlContext>
#include <QtQml>
int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    //设置窗口图标
    app.setWindowIcon(QIcon("icon.svg"));

    //注册计时线程,并将计时线程移动到工作线程
    TimerThread timerThread;
    QThread workerThread;
    timerThread.moveToThread(&workerThread);

    //启动工作线程
    workerThread.start();

    QQmlApplicationEngine engine;

    qmlRegisterType<TimerThread>("com.timerthread",1,0,"TimerThread");

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
