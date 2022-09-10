#ifndef WEBSOCKETHANDLER_H
#define WEBSOCKETHANDLER_H

#include <QObject>
#include <QWebSocket>
#include "messageprossecorhandler.h"

class WebSocketHandler : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketHandler(QObject *parent = nullptr);
    ~WebSocketHandler();

    Q_INVOKABLE void connectToServer(QString hostAddress);


signals:
    void newMessageReadyForProcessing(QString message);

public slots:
    void onConnected();
    void onTextMessageRecieved(QString message);
    void sendMessageToServer(QString message);


private:
    QWebSocket * m_webSocket;

};

#endif // WEBSOCKETHANDLER_H
