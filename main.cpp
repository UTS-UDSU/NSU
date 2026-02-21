#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "tcpconnectioncontroller.h"
#include "mavlinkcontroller.h"


int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QGuiApplication app(argc, argv);

    qmlRegisterType<MavlinkController>("edu.udsu", 1, 0, "MavlinkController");
    qmlRegisterType<TCPConnectionController>("edu.udsu", 1, 0, "TCPConnectionController");

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("SimpleGCS", "Main");

    return app.exec();
}
