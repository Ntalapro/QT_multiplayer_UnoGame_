#ifndef WEBSOCKETHANDLER_H
#define WEBSOCKETHANDLER_H

#include <QObject>
#include <QtWebSockets/QWebSocketServer>
#include <QtWebSockets/QWebSocket>
#include <QMap>
class WebSocketHandler : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketHandler(QObject *parent = nullptr);
    ~WebSocketHandler();

    void sendTextMessageToClient(QString message, QString clientID);
    void sendTextMessageToMultipleClients(QString message, QStringList clientIDS);

signals:
    void newMessageToProcess(QString message);

public slots:

    void onNewSocketConnection();
    void onTextMessageRecieved(QString message);
    void onSocketDsiconnected();

private:

    QWebSocketServer * m_socketserver;
    QMap<QString,QWebSocket*>  m_clientlist;
};

#endif // WEBSOCKETHANDLER_H
