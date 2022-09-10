#ifndef MESSAGEPROSSECORHANDLER_H
#define MESSAGEPROSSECORHANDLER_H

#include <QObject>

class MessageProssecorHandler : public QObject
{
    Q_OBJECT
public:
    explicit MessageProssecorHandler(QObject *parent = nullptr);

    void processMessage(QString message);
    QStringList clientHand = {"qrc:Cards/back.png"};
    bool yourTurn = false;
    QString stackCard;
    QString deckCard;
    //QString add_or_sub = "m";
    QStringList oppCards = {"qrc:Cards/back.png",
                            "qrc:Cards/back.png",
                            "qrc:Cards/back.png",
                            "qrc:Cards/back.png",
                            "qrc:Cards/back.png",
                            "qrc:Cards/back.png",
                            "qrc:Cards/back.png"};
    QString pickNum;
    bool oppWon_ = false;


signals:
    void uniqueIDRegistration(QString uniqueID);
    void newLobby(QString lobbyID,QStringList clients);
    void lobbyListUpdated(QStringList newLobbyList);
    void newLobbyMessage(QString message);
    void lobbyReadyListChanged(QStringList clientReadyList);
    void gameStarting();
    void cardsDealt(QStringList clientHand);
    void turnChanged(bool turn);
    void deckCardChanged(QString card);
    void stackCardChanged(QString card);
    //void add_subChanged(QString add_sub);
    void oppCardsChanged(QStringList list);
    void pickNumChanged_(QString num);
    void oppWon(bool opp);
};

#endif // MESSAGEPROSSECORHANDLER_H
