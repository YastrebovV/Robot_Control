#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "appcore.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    AppCore appCore;    // Создаём ядро приложения
    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();    // Создаём корневой контекст
        /* Загружаем объект в контекст для установки соединения,
         * а также определяем имя, по которому будет происходить соединение
         * */
    context->setContextProperty("appCore", &appCore);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
