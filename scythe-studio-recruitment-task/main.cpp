#include "filesystemwatcherservice.h"
#include "watchpathmodel.h"
#include "eventlogmodel.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    FileSystemWatcherService fileSystemWatcherService;
    engine.rootContext()->setContextProperty("fileSystemWatcherService", &fileSystemWatcherService);
    engine.rootContext()->setContextProperty("WatchPathModel", WatchPathModel::instance());
    engine.rootContext()->setContextProperty("EventLogModel", EventLogModel::instance());

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);


    return app.exec();
}
