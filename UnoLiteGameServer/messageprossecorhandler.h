#ifndef MESSAGEPROSSECORHANDLER_H
#define MESSAGEPROSSECORHANDLER_H

#include <QObject>

class MessageProssecorHandler : public QObject
{
    Q_OBJECT
public:
    explicit MessageProssecorHandler(QObject *parent = nullptr);


signals:
    void createGameRequest(QString uniqueID);
    void joinGameLobbyRequest(QString lobbyID,QString uniqueID);
    void messageLobbyRequest(QString message,QString lobbyID,QString senderID);
    void clientReadyToPlay(QString uniqueID);
    void sendStackCard(QString card,QString id);
    void sendDeckCard(QString id,QString num);
    void sendWinner(QString id);


public slots:
    void processMessage(QString message);

};

#endif // MESSAGEPROSSECORHANDLER_H
