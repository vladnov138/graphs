#include "src/gamecontroller/gamecontroller.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    const int DEPTH = 7;
    AlphaBeta ab(DEPTH);
    GameEnemy enemy(ab);
    GameController gameController(&enemy);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/4_in_row/main.qml"));
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
    engine.rootContext()->setContextProperty("gameController", &gameController);

    return app.exec();
}
