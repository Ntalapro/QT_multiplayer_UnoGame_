#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include "messageprossecorhandler.h"
#include <QFile>
#include <QTextStream>

class GameManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString roomlobbycode READ roomlobbycode WRITE setRoomlobbycode NOTIFY roomlobbycodeChanged)
    Q_PROPERTY(QStringList clientsInLobby READ clientsInLobby WRITE setClientsInLobby NOTIFY clientsInLobbyChanged)
    Q_PROPERTY(QStringList dealtCards READ dealtCards WRITE setDealtCards NOTIFY dealtCardsChanged)
    Q_PROPERTY(bool yourTurn READ yourTurn WRITE setYourTurn NOTIFY yourTurnChanged)
    Q_PROPERTY(QString newStackCard READ newStackCard WRITE setNewStackCard NOTIFY newStackCardChanged)
    Q_PROPERTY(QString newDeckCard READ newDeckCard WRITE setNewDeckCard NOTIFY newDeckCardChanged)
    //Q_PROPERTY(QString add_sub READ add_sub WRITE setAdd_sub NOTIFY add_subChanged)
    Q_PROPERTY(QStringList oppCards READ oppCards WRITE setOppCards NOTIFY oppCardsChanged)
    Q_PROPERTY(QString pickNumber READ pickNumber WRITE setPickNumber NOTIFY pickNumberChanged)
    Q_PROPERTY(bool oppWonGame READ oppWonGame WRITE setoppWonGame NOTIFY oppWonGameChanged)
    Q_PROPERTY(QStringList rankList READ rankList WRITE setrankList NOTIFY rankListChanged)



    //COMPUTER PLAYER
    Q_PROPERTY(bool yTurn READ yTurn WRITE setyTurn NOTIFY yTurnChanged)
    Q_PROPERTY(QString stackCard READ stackCard WRITE setStackCard NOTIFY stackCardChanged)
    Q_PROPERTY(QStringList myHand READ myHand WRITE setMyHand NOTIFY myHandChanged)
    Q_PROPERTY(QStringList compHand READ compHand WRITE setCompHand NOTIFY compHandChanged)
    Q_PROPERTY(bool have READ have WRITE setHave NOTIFY haveChanged)
    Q_PROPERTY(QStringList compCards READ compCards WRITE setCompCards NOTIFY compCardsChanged)


public:
    explicit GameManager(QObject *parent = nullptr);
    ~GameManager();
    QString roomlobbycode();
    QStringList clientsInLobby();
    QStringList dealtCards();
    bool yourTurn();
    QString newStackCard();
    QString newDeckCard();
    QStringList oppCards();
    QString pickNumber();
    bool oppWonGame();
    QStringList rankList();


    bool yTurn();
    QStringList compHand();
    QStringList myHand();
    QString stackCard();
    bool have();
    QStringList compCards();



    Q_INVOKABLE void createGameRequest();
    Q_INVOKABLE void joinGameRequest(QString lobbyId);
    Q_INVOKABLE void sendMessageToLobby(QString message);
    Q_INVOKABLE bool isClientReady(QString clientID);
    Q_INVOKABLE void readyToPlay();
    Q_INVOKABLE void cardClicked(QString card, bool turn);
    Q_INVOKABLE void deckCardClicked(QString picknum, bool turn);
    Q_INVOKABLE void winner();
    Q_INVOKABLE void writeFile(QString filename,QString data);
    Q_INVOKABLE void readFile(QString filename);
    //Q_INVOKABLE void compTurn();
    Q_INVOKABLE void playCard(QString card);
    Q_INVOKABLE void deckPick(int num);

    bool yTurn_ = true;
    QStringList myHand_;
    QStringList compHand_;
    QString stackCard_ = "qrc:/Cards/1_b.png";
    bool have_ = false;
    QStringList compCards_ = {"qrc:/Cards/back.png",
                              "qrc:/Cards/back.png",
                              "qrc:/Cards/back.png",
                              "qrc:/Cards/back.png",
                              "qrc:/Cards/back.png",
                              "qrc:/Cards/back.png",
                              "qrc:/Cards/back.png"};

    QList<QString> m_deckCards;
    void shuffleDeck();

    QStringList temp;
    QStringList topNames;



    void most_occurred_(QStringList names, int size);
public slots:
    void setRoomlobbycode(QString lobbycode);
    void setClientsInLobby(QStringList clientList);
    void setDealtCards(QStringList dealtCards);
    void setYourTurn(bool turn);
    void setNewStackCard(QString card);
    void setNewDeckCard(QString card);
    void setOppCards(QStringList list);
    void setPickNumber(QString num);
    void setoppWonGame(bool opp);
    void processSocketMessage(QString message);
    void registerUniqueID(QString uniqueID);
    void setMyHand(QStringList hand);
    void setCompHand(QStringList hand);
    void lobbyJoined(QString lobbyID, QStringList clients);
    void newClientReadyList(QStringList clientReadyList);
    void setStackCard(QString card);
    void setyTurn(bool turn);
    void setHave(bool doesHave);
    void setCompCards(QStringList hand);
    void compTurn();
    void setrankList(QStringList top);

signals:
    void roomlobbycodeChanged();
    void clientsInLobbyChanged();
    void dealtCardsChanged();
    void newLobbyMessage(QString message);
    void newMessageReadyToSend(QString message);
    void inGameLobby();
    void readyListChanged();
    void gameStarting();
    void yourTurnChanged();
    void newStackCardChanged();
    void newDeckCardChanged();
    void oppCardsChanged();
    void pickNumberChanged();
    void oppWonGameChanged();
    void yTurnChanged();
    void compHandChanged();
    void myHandChanged();
    void stackCardChanged();
    void haveChanged();
    void compCardsChanged();
    void computer();
    void rankListChanged();

private:
    QString m_clientID;
    QString m_roomLobbyCode;
    QStringList m_clientsInLobby;
    QStringList m_readyClientList;
    MessageProssecorHandler * m_messageHanlder;
};

#endif // GAMEMANAGER_H
