#include "gamemanager.h"
#include <random>

GameManager::GameManager(QObject *parent)
    : QObject{parent}
{
    m_socketHandler = new WebSocketHandler(this);
    m_messageProcessHandler = new MessageProssecorHandler(this);

    connect(m_socketHandler,&WebSocketHandler::newMessageToProcess,m_messageProcessHandler,
            &MessageProssecorHandler::processMessage);
    connect(m_messageProcessHandler,&MessageProssecorHandler::createGameRequest,
            this,&GameManager::createGameLobbyRequest);
    connect(m_messageProcessHandler,&MessageProssecorHandler::joinGameLobbyRequest,
            this,&GameManager::joinGameLobbyRequest);
    connect(m_messageProcessHandler,&MessageProssecorHandler::messageLobbyRequest,
            this,&GameManager::messageLobbyRequest);
    connect(m_messageProcessHandler,&MessageProssecorHandler::clientReadyToPlay,
            this,&GameManager::userReadyToPlay);



}

GameManager::~GameManager()
{
    m_socketHandler->deleteLater();
}

void GameManager::createGameLobbyRequest(QString uniqueID)
{
    std::default_random_engine generator;
    generator.seed(QDateTime::currentMSecsSinceEpoch());

    std::uniform_int_distribution<int> idGenerator(1000,9999);
    QString newLobbyID = QString::number(idGenerator(generator));

    while(m_gamelobbyMap.keys().contains(newLobbyID)){
        newLobbyID = QString::number(idGenerator(generator));
    }

    GameLobbyHandler * newGameLobbyHandler = new GameLobbyHandler(newLobbyID,this);

    connect(m_messageProcessHandler,&MessageProssecorHandler::sendDeckCard,
            newGameLobbyHandler,&GameLobbyHandler::_deckCard);
    connect(m_messageProcessHandler,&MessageProssecorHandler::sendStackCard,
            newGameLobbyHandler,&GameLobbyHandler::_stackCard);
    connect(m_messageProcessHandler,&MessageProssecorHandler::sendWinner,
            newGameLobbyHandler,&GameLobbyHandler::sendWinner_);

    connect(newGameLobbyHandler,&GameLobbyHandler::userReadyListChanged,
            this,&GameManager::userReadyListChanged);
    connect(newGameLobbyHandler,&GameLobbyHandler::gameReadyToBegin,
            this,&GameManager::gameLobbyReadToBegin);
    connect(newGameLobbyHandler,&GameLobbyHandler::_deckCard1,
            this,&GameManager::sendDeckC);
    connect(newGameLobbyHandler,&GameLobbyHandler::_stackCard2,
            this,&GameManager::sendStackC);
    connect(newGameLobbyHandler,&GameLobbyHandler::oppWon,
            this,&GameManager::winner);

    newGameLobbyHandler->addClient(uniqueID);
    m_gamelobbyMap[newLobbyID]=newGameLobbyHandler;

    qDebug()<<"new game lobby created: "+newLobbyID;
    m_socketHandler->sendTextMessageToClient("type:newLobbycreated;payload:"+newLobbyID+";clientList:"+uniqueID,uniqueID);
}

void GameManager::joinGameLobbyRequest(QString lobbyID, QString uniqueID)
{
    if(m_gamelobbyMap.contains(lobbyID)){
        GameLobbyHandler * existingLobby = m_gamelobbyMap[lobbyID];
        existingLobby->addClient(uniqueID);

        m_socketHandler->sendTextMessageToMultipleClients("type:updatedClientList;payload:"+
                                                          existingLobby->ClientsInLobby(),existingLobby->ClientsInLobbyList());
        m_socketHandler->sendTextMessageToClient("type:joinSuccess;payload:"+lobbyID+
                                                 ";clientList:"+existingLobby->ClientsInLobby(),uniqueID);

    }
    else{
        m_socketHandler->sendTextMessageToClient("type:joinError;payload:DNE", uniqueID);
    }
}

void GameManager::messageLobbyRequest(QString message, QString lobbyID, QString senderID)
{
    if(m_gamelobbyMap.contains(lobbyID)){
      GameLobbyHandler * existingLobby = m_gamelobbyMap[lobbyID];
      m_socketHandler->sendTextMessageToMultipleClients("type:lobbyMessage;payload:"+message+";sender:"
                                                        +senderID,existingLobby->ClientsInLobbyList());
    }
}

void GameManager::userReadyListChanged()
{
    GameLobbyHandler * existingLobby = qobject_cast<GameLobbyHandler*>(sender());
    m_socketHandler->sendTextMessageToMultipleClients("type:lobbyreadyListChanged;payload:"+existingLobby->whoIsReady(),
                                                      existingLobby->ClientsInLobbyList());

}

void GameManager::userReadyToPlay(QString uniqueID)
{
    qDebug()<<"user ready: "<<uniqueID;
    QList<GameLobbyHandler*> gameLobbyList = m_gamelobbyMap.values();
    foreach(GameLobbyHandler * existingLobby, gameLobbyList)
        existingLobby->userReadyToPlay(uniqueID);
}

void GameManager::gameLobbyReadToBegin()
{
    GameLobbyHandler * existingLobby = qobject_cast<GameLobbyHandler*>(sender());
    m_socketHandler->sendTextMessageToMultipleClients("type:gameReadyToBegin;payload:0",
                                                      existingLobby->ClientsInLobbyList());

    if(existingLobby->ClientsInLobbyList().length() == 2)
        sendCardsToUsers(existingLobby);

}

void GameManager::sendStackC(QString card,QString id)
{
    qDebug()<<"sending stack card!";
     GameLobbyHandler * existingLobby = qobject_cast<GameLobbyHandler*>(sender());

     m_socketHandler->sendTextMessageToMultipleClients("type:newStackCard;payload:"+card,
                                                       existingLobby->ClientsInLobbyList());
     if(existingLobby->ClientsInLobbyList().front() == id){
         m_socketHandler->sendTextMessageToClient("type:otherClientHandSub;payload:0",
                                                  existingLobby->ClientsInLobbyList().back());
     }else if(existingLobby->ClientsInLobbyList().back() == id){
         m_socketHandler->sendTextMessageToClient("type:otherClientHandSub;payload:0",
                                                  existingLobby->ClientsInLobbyList().front());
     }

}

void GameManager::sendDeckC(QString id, QString num)
{
    qDebug()<<"sending deck card!";
    GameLobbyHandler * existingLobby = qobject_cast<GameLobbyHandler*>(sender());

    QString card = existingLobby->m_deckCards.at(0);
    m_socketHandler->sendTextMessageToMultipleClients("type:newDeckCard;payload:"+card,
                                                      existingLobby->ClientsInLobbyList());
    existingLobby->m_deckCards.pop_front();
    if(existingLobby->ClientsInLobbyList().front() == id){
        m_socketHandler->sendTextMessageToClient("type:otherClientHandAdd;payload:0",
                                                 existingLobby->ClientsInLobbyList().back());
        m_socketHandler->sendTextMessageToClient("type:PickNum;payload:"+num,
                                                 existingLobby->ClientsInLobbyList().front());
    }else if(existingLobby->ClientsInLobbyList().back() == id){
        m_socketHandler->sendTextMessageToClient("type:otherClientHandAdd;payload:0",
                                                 existingLobby->ClientsInLobbyList().front());
        m_socketHandler->sendTextMessageToClient("type:PickNum;payload:"+num,
                                                 existingLobby->ClientsInLobbyList().back());
    }

}

void GameManager::winner(QString id)
{
    GameLobbyHandler * existingLobby = qobject_cast<GameLobbyHandler*>(sender());
    if(existingLobby->ClientsInLobbyList().front() == id){
        m_socketHandler->sendTextMessageToClient("type:oppWon;payload:0",
                                                 existingLobby->ClientsInLobbyList().back());

    }else if(existingLobby->ClientsInLobbyList().back() == id){
        m_socketHandler->sendTextMessageToClient("type:oppWon;payload:0",
                                                 existingLobby->ClientsInLobbyList().front());
    }

}

void GameManager::sendCardsToUsers( GameLobbyHandler * existingLobby)
{
    QStringList clientCards1;
    QStringList clientCards2;
    QString cards1;
    QString cards2;
    for(int i=0;i<7;i++){
        clientCards1.append(existingLobby->m_deckCards.at(i));
        existingLobby->m_deckCards.pop_front();

    }
    for(int i=0;i<7;i++){
        clientCards2.append(existingLobby->m_deckCards.at(i));
        existingLobby->m_deckCards.pop_front();

    }
    cards1=clientCards1.join(",");
    cards2=clientCards2.join(",");
    m_socketHandler->sendTextMessageToMultipleClients("type:newDeckCard;payload:"+existingLobby->m_deckCards.front(),
                                                      existingLobby->ClientsInLobbyList());
    existingLobby->m_deckCards.pop_front();
    m_socketHandler->sendTextMessageToMultipleClients("type:newStackCard;payload:"+existingLobby->m_deckCards.back(),
                                                      existingLobby->ClientsInLobbyList());
    m_socketHandler->sendTextMessageToClient("type:fromDeckCard;payload:"+ cards1
                                                     , existingLobby->ClientsInLobbyList().back());
    m_socketHandler->sendTextMessageToClient("type:fromDeckCard;payload:"+ cards2
                                                 , existingLobby->ClientsInLobbyList().first());

}
















