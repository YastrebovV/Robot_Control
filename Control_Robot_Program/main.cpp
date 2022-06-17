#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QQmlProperty>
#include <QQuickView>
#include <QQuickItem>
#include <QMetaObject>
#include <QDebug>

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

//        // Вызов метода QML
//        QVariant val_return; // Возвращаемое значение
//        QVariant val_arg = "=. =!"; // Значение параметра
//        // Параметры Q_RETURN_ARG () и Q_Arg () должны быть сформулированы как тип QVariant
//        QMetaObject::invokeMethod(obj,
//                             "qml_method",
//                             Q_RETURN_ARG(QVariant,val_return),
//                             Q_ARG(QVariant,val_arg));
//        qDebug () << "qml method return value" << val_return; // Функция возвращает "ok"

        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
