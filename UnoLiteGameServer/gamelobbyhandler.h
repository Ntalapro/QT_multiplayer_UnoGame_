#ifndef GAMELOBBYHANDLER_H
#define GAMELOBBYHANDLER_H

#include <QObject>
#include <QMap>



class GameLobbyHandler : public QObject
{
    Q_OBJECT
public:
    explicit GameLobbyHandler(QString lobbyID,QObject *parent );
    void addClient(QString clientID);
    QString ClientsInLobby();
    QStringList ClientsInLobbyList();

    void userReadyToPlay(QString clientID);
    QString whoIsReady();
    void shuffleDeck();
    QList<QString> m_deckCards;

public slots:
    void _deckCard(QString id,QString num);
    void _stackCard(QString card,QString id);
    void sendWinner_(QString id);

signals:
    void userReadyListChanged();
    void gameReadyToBegin();
    void _deckCard1(QString id,QString num);
    void _stackCard2(QString card,QString id);
    void oppWon(QString id);



private:
    QString m_lobbyID;
    QList<QString> m_gameClientlist;
    QMap<QString, bool> m_clientReadyList;


};

#endif // GAMELOBBYHANDLER_H
