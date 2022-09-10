#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include "websockethandler.h"
#include "messageprossecorhandler.h"
#include "gamelobbyhandler.h"

class GameManager : public QObject
{
    Q_OBJECT
public:
    explicit GameManager(QObject *parent = nullptr);
    ~GameManager();

    void sendCardsToUsers(GameLobbyHandler * existingLobby);

signals:

public slots:
    void createGameLobbyRequest(QString uniqueID);
    void joinGameLobbyRequest(QString lobbyID,QString uniqueID);
    void messageLobbyRequest(QString message,QString lobbyID,QString senderID);
    void userReadyListChanged();
    void userReadyToPlay(QString uniqueID);
    void gameLobbyReadToBegin();
    void sendStackC(QString card,QString id);
    void sendDeckC(QString id,QString num);
    void winner(QString id);


private:
    WebSocketHandler *m_socketHandler;
    MessageProssecorHandler * m_messageProcessHandler;
    QMap<QString, GameLobbyHandler *> m_gamelobbyMap;
};

#endif // GAMEMANAGER_H
