#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>
//#include <QQuickWindow>

#include "control.h"


#ifdef Q_OS_ANDROID


#else
    #if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        #include "myfilter.h"
    #endif
#endif


int main(int argc, char *argv[])
{

#ifdef Q_OS_ANDROID

#else
    #if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    #endif

    #ifdef Q_OS_WIN
        //qputenv("QT_QUICK_BACKEND","software");
        //QQuickWindow::setSceneGraphBackend("software");
    #endif
#endif

    QGuiApplication app(argc, argv);
    QGuiApplication::setWindowIcon(QIcon(":/image/icon.png"));

#ifdef Q_OS_ANDROID
    const QUrl url(QStringLiteral("qrc:/qml6/main.qml"));
#else
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        qmlRegisterType<MyFilter>("my.filter", 1, 0, "MyFilter");
        const QUrl url(QStringLiteral("qrc:/qml5/main.qml"));
#else
    const QUrl url(QStringLiteral("qrc:/qml6/main.qml"));
#endif
#endif

    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    QQmlContext* context = engine.rootContext();
    Control *a_pCon = new Control(&engine);
    context->setContextProperty("contextMain", a_pCon );

    engine.load(url);

    return app.exec();
}
