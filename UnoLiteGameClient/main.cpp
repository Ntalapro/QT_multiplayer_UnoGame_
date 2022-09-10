#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QStringListModel>

#include <QLocale>
#include "websockethandler.h"
#include "gamemanager.h"


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    WebSocketHandler socketHandler;
    //socketHandler.connectToServer("ws://127.0.0.1:4001");

    GameManager gameManager;

    QObject::connect(&socketHandler,&WebSocketHandler::newMessageReadyForProcessing,
                     &gameManager,&GameManager::processSocketMessage);

    QObject::connect(&gameManager,&GameManager::newMessageReadyToSend,&socketHandler,
                     &WebSocketHandler::sendMessageToServer);

    QStringListModel m_model;
    m_model.setStringList(gameManager.dealtCards());

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    QQmlContext * context = engine.rootContext();
    context->setContextProperty("webSocketHandler", &socketHandler);
    context->setContextProperty("gameManager", &gameManager);
    context->setContextProperty("myModel", &m_model);

    return app.exec();
}
