#include "gamelobbyhandler.h"
#include "qdebug.h"
#include<list>

GameLobbyHandler::GameLobbyHandler(QString lobbyID,QObject *parent)
    : QObject{parent}
    ,m_lobbyID( lobbyID)
{
    m_clientReadyList.clear();
    m_deckCards.append("qrc:/Cards/0_b.png");
    m_deckCards.append("qrc:/Cards/0_g.png");
    m_deckCards.append("qrc:/Cards/0_r.png");
    m_deckCards.append("qrc:/Cards/0_y.png");
    m_deckCards.append("qrc:/Cards/1_b.png");
    m_deckCards.append("qrc:/Cards/1_g.png");
    m_deckCards.append("qrc:/Cards/1_r.png");
    m_deckCards.append("qrc:/Cards/1_y.png");
    m_deckCards.append("qrc:/Cards/2_b.png");
    m_deckCards.append("qrc:/Cards/2_g.png");
    m_deckCards.append("qrc:/Cards/2_r.png");
    m_deckCards.append("qrc:/Cards/2_y.png");
    m_deckCards.append("qrc:/Cards/3_b.png");
    m_deckCards.append("qrc:/Cards/3_g.png");
    m_deckCards.append("qrc:/Cards/3_r.png");
    m_deckCards.append("qrc:/Cards/3_y.png");
    m_deckCards.append("qrc:/Cards/4_b.png");
    m_deckCards.append("qrc:/Cards/4_g.png");
    m_deckCards.append("qrc:/Cards/4_r.png");
    m_deckCards.append("qrc:/Cards/4_y.png");
    m_deckCards.append("qrc:/Cards/5_b.png");
    m_deckCards.append("qrc:/Cards/5_g.png");
    m_deckCards.append("qrc:/Cards/5_r.png");
    m_deckCards.append("qrc:/Cards/5_y.png");
    m_deckCards.append("qrc:/Cards/6_b.png");
    m_deckCards.append("qrc:/Cards/6_g.png");
    m_deckCards.append("qrc:/Cards/6_r.png");
    m_deckCards.append("qrc:/Cards/6_y.png");
    m_deckCards.append("qrc:/Cards/7_b.png");
    m_deckCards.append("qrc:/Cards/7_g.png");
    m_deckCards.append("qrc:/Cards/7_r.png");
    m_deckCards.append("qrc:/Cards/8_b.png");
    m_deckCards.append("qrc:/Cards/8_g.png");
    m_deckCards.append("qrc:/Cards/8_r.png");
    m_deckCards.append("qrc:/Cards/8_y.png");
    m_deckCards.append("qrc:/Cards/9_b.png");
    m_deckCards.append("qrc:/Cards/9_g.png");
    m_deckCards.append("qrc:/Cards/9_r.png");
    m_deckCards.append("qrc:/Cards/9_y.png");
    m_deckCards.append("qrc:/Cards/d2_b.png");
    m_deckCards.append("qrc:/Cards/d2_g.png");
    m_deckCards.append("qrc:/Cards/d2_r.png");
    m_deckCards.append("qrc:/Cards/d2_y.png");
    m_deckCards.append("qrc:/Cards/w4_b.png");
    m_deckCards.append("qrc:/Cards/w4_g.png");
    m_deckCards.append("qrc:/Cards/w4_y.png");
    m_deckCards.append("qrc:/Cards/w4_r.png");

    shuffleDeck();
}

void GameLobbyHandler::addClient(QString clientID)
{
     if(!m_gameClientlist.contains(clientID))
         m_gameClientlist.append(clientID);

     m_clientReadyList.clear();
     foreach(const QString & client, m_gameClientlist){
         m_clientReadyList[client]= false;
     }
     emit userReadyListChanged();
}

QString GameLobbyHandler::ClientsInLobby()
{
    QString ret;
    foreach(const QString & client, m_gameClientlist){
        ret.append(client + ",");
    }ret.chop(1);

    return ret;
}

QStringList GameLobbyHandler::ClientsInLobbyList()
{
    QStringList ret = ClientsInLobby().split(QRegExp(","));
    return ret;
}

void GameLobbyHandler::userReadyToPlay(QString clientID)
{
    if(m_gameClientlist.contains(clientID)){

        m_clientReadyList[clientID]=true;
    }
    emit userReadyListChanged();

    bool notReady = false;
    foreach(const QString & clientID, m_clientReadyList.keys()){
        if(!m_clientReadyList[clientID])
            notReady = true;
    }
    if(!notReady){
        emit gameReadyToBegin();
    }
}

QString GameLobbyHandler::whoIsReady()
{
    QString returnValue;
    foreach(const QString & client, m_clientReadyList.keys()){
        if(m_clientReadyList[client]){
            returnValue.append(client+",");
        }
    }
    returnValue.chop(1);

    return returnValue;
}

void GameLobbyHandler::shuffleDeck()
{
    std::random_shuffle ( m_deckCards.begin(), m_deckCards.end() );
    qDebug()<<"deck shuffled";
}

void GameLobbyHandler::_deckCard(QString id,QString num)
{
    emit _deckCard1(id,num);
}

void GameLobbyHandler::_stackCard(QString card,QString id)
{
    emit _stackCard2(card,id);
}

void GameLobbyHandler::sendWinner_(QString id)
{
    emit oppWon(id);
}

