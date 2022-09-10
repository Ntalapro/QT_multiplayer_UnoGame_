#include "gamemanager.h"
#include "qdebug.h"
#include <chrono>
#include <thread>

#include <QFile>

GameManager::GameManager(QObject *parent)
    : QObject{parent}
    ,m_clientID(QString())
    , m_roomLobbyCode(QString())
    ,m_clientsInLobby(QStringList())
    ,m_readyClientList(QStringList())
{
    m_messageHanlder = new MessageProssecorHandler(this);
    connect(m_messageHanlder,&MessageProssecorHandler::uniqueIDRegistration,
            this,&GameManager::registerUniqueID);
    connect(m_messageHanlder,&MessageProssecorHandler::newLobby,
            this,&GameManager::lobbyJoined);
    connect(m_messageHanlder,&MessageProssecorHandler::lobbyListUpdated,
            this,&GameManager::setClientsInLobby);
    connect(m_messageHanlder,&MessageProssecorHandler::cardsDealt,
            this,&GameManager::setDealtCards);
    connect(m_messageHanlder,&MessageProssecorHandler::turnChanged,
            this,&GameManager::setYourTurn);
    connect(m_messageHanlder,&MessageProssecorHandler::newLobbyMessage,
            this,&GameManager::newLobbyMessage);
    connect(m_messageHanlder,&MessageProssecorHandler::lobbyReadyListChanged,
            this,&GameManager::newClientReadyList);
    connect(m_messageHanlder,&MessageProssecorHandler::gameStarting,
            this,&GameManager::gameStarting);
    connect(m_messageHanlder,&MessageProssecorHandler::deckCardChanged,
            this,&GameManager::setNewDeckCard);
    connect(m_messageHanlder,&MessageProssecorHandler::stackCardChanged,
            this,&GameManager::setNewStackCard);
    connect(m_messageHanlder,&MessageProssecorHandler::oppCardsChanged,
            this,&GameManager::setOppCards);
    connect(m_messageHanlder,&MessageProssecorHandler::pickNumChanged_,
            this,&GameManager::setPickNumber);
    connect(m_messageHanlder,&MessageProssecorHandler::oppWon,
            this,&GameManager::setoppWonGame);
    connect(this,&GameManager::computer,
            this,&GameManager::compTurn);




    //computer side
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

    for(int i=0;i<7;i++){
        myHand_.append(m_deckCards[0]);
        m_deckCards.pop_front();
    }
    for(int i=0;i<7;i++){
        compHand_.append(m_deckCards[0]);
        m_deckCards.pop_front();
    }
}
GameManager::~GameManager(){
    m_messageHanlder->deleteLater();
}
void GameManager::shuffleDeck()
{
    std::random_shuffle ( m_deckCards.begin(), m_deckCards.end() );
    qDebug()<<"deck shuffled";
}


QString GameManager::roomlobbycode()
{
    return m_roomLobbyCode;
}

QStringList GameManager::clientsInLobby()
{
    return m_clientsInLobby;
}

QStringList GameManager::dealtCards()
{
   return m_messageHanlder->clientHand;
}
bool GameManager:: yourTurn(){
    return m_messageHanlder->yourTurn;
}

QString GameManager::newStackCard()
{
 return m_messageHanlder->stackCard;
}
QString GameManager::newDeckCard()
{
    return m_messageHanlder->deckCard;
}

QStringList GameManager::oppCards()
{

    return m_messageHanlder->oppCards;
}

QString GameManager::pickNumber()
{
    return m_messageHanlder->pickNum;
}

bool GameManager::oppWonGame()
{
    return m_messageHanlder->oppWon_;
}

QStringList GameManager::rankList()
{
    return topNames;
}

bool GameManager::yTurn()
{
    return yTurn_;

}

QStringList GameManager::compHand()
{
    return compHand_;
}

QStringList GameManager::myHand()
{
    return myHand_;
}

QString GameManager::stackCard()
{
    return stackCard_;
}

bool GameManager::have()
{
    return have_;
}

QStringList GameManager::compCards()
{
    return compCards_;
}

void GameManager::createGameRequest()
{
    //"type:creategame;payload:0;sender:5555"
    m_messageHanlder->yourTurn = true;
    emit m_messageHanlder->turnChanged(m_messageHanlder->yourTurn);

    emit newMessageReadyToSend("type:creategame;payload:0;sender:" + m_clientID);
}

void GameManager::joinGameRequest(QString lobbyId)
{

    emit newMessageReadyToSend("type:joingame;payload:"+lobbyId+";sender:" + m_clientID);
}

void GameManager::sendMessageToLobby(QString message)
{

    emit newMessageReadyToSend("type:message;payload:"+message+";lobbyID:"+m_roomLobbyCode+";sender:"+m_clientID);
}

bool GameManager::isClientReady(QString clientID)
{
    return m_readyClientList.contains(clientID);
}

void GameManager::readyToPlay()
{
    emit newMessageReadyToSend("type:readyToPlay;payload:1;sender:"+m_clientID);
}

void GameManager::cardClicked(QString card,bool turn)
{
    m_messageHanlder->yourTurn = turn;
    emit m_messageHanlder->turnChanged(m_messageHanlder->yourTurn);
    emit newMessageReadyToSend("type:cardClicked;payload:"+card+";sender:"+m_clientID);
}

void GameManager::deckCardClicked(QString picknum,bool turn)
{
    m_messageHanlder->yourTurn = turn;
    emit m_messageHanlder->turnChanged(m_messageHanlder->yourTurn );
    emit newMessageReadyToSend("type:deckClicked;sender:"+m_clientID+";pick:"+picknum);
    qDebug()<<picknum;
}

void GameManager::winner()
{
    emit newMessageReadyToSend("type:won;sender:"+m_clientID);
}

void GameManager::writeFile(QString filename, QString data)
{
    QFile file(filename);
       if(!file.open(QIODevice::Append))
       {
           qDebug() << file.errorString();

       }

       QTextStream stream(&file);
         stream  << data<<"\n";

       file.close();
}
void GameManager:: most_occurred_(QStringList names, int size)
{
  int max_count = 0;

  for (int i=0; i<size; i++)
  {
   int count=1;
   for (int j=i+1;j<size;j++)
       if (names[i]==names[j])
           count++;
   if (count>max_count)
      max_count = count;
  }

  for (int i=0;i<size;i++)
  {
   int count=1;
   for (int j=i+1;j<size;j++)
       if (names[i]==names[j])
           count++;
   if (count==max_count)
       topNames.push_front(names[i]);
   setrankList(topNames);
  }
 }

void GameManager::readFile(QString filename)
{
    QFile file(filename);
        if(!file.exists())
        {
            qDebug() << "File not found";
            return;
        }

        if(!file.open(QIODevice::ReadOnly))
        {
            qDebug() << file.errorString();
            return;
        }

        QTextStream stream(&file);
        QStringList data = QStringList();

        while (!stream.atEnd()) {
            data.append(stream.readLine());
            qInfo() << data;
        }
        temp = data;

        file.close();
        most_occurred_(temp, temp.length());
}

void GameManager::compTurn()
{
    //setyTurn(turn);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    //()<<"in comp play: "<<compHand_;
    for(int i=0;i<compHand_.length();i++){
        if(stackCard_.length() == 18){
            qDebug()<<"in 18";
            if(compHand_[i].contains(stackCard_[11]) == true || compHand_[i].contains(stackCard_[13]) == true ){
                qDebug()<<"in 18"<<compHand_[i];
                setStackCard(compHand_[i]);
                compHand_.removeOne(compHand_[i]);
                setHave(true);
                setyTurn(true);
                compCards_.pop_back();
                setCompCards(compCards_);
                break;
            }
        }
        else {
            qDebug()<<"in 19";
            if(compHand_[i].contains(stackCard_[12]) || compHand_[i].contains(stackCard_[14]) ){
                qDebug()<<"in 19"<<compHand_[i];
                setStackCard(compHand_[i]);
                compHand_.removeOne(compHand_[i]);
                setHave(true);
                setyTurn(true);
                compCards_.pop_back();
                setCompCards(compCards_);
                break;
            }
        }
    }
    if(have_ == false){
        qDebug()<<"comp picks";
       if(stackCard_[11] == "d"){
           qDebug()<<"comp picks 2";
           compCards_.append("qrc:/Cards/back.png");
           compCards_.append("qrc:/Cards/back.png");
           setCompCards(compCards_);

           compHand_.append(m_deckCards[0]);
           m_deckCards.pop_front();
           compHand_.append(m_deckCards[0]);
           m_deckCards.pop_front();


           setyTurn(true);
       }else if (stackCard_[11] == "w"){
           qDebug()<<"comp picks 4";
           compCards_.append("qrc:/Cards/back.png");
           compCards_.append("qrc:/Cards/back.png");
           compCards_.append("qrc:/Cards/back.png");
           compCards_.append("qrc:/Cards/back.png");
           setCompCards(compCards_);

           compHand_.append(m_deckCards[0]);
           m_deckCards.pop_front();
           compHand_.append(m_deckCards[0]);
           m_deckCards.pop_front();
           compHand_.append(m_deckCards[0]);
           m_deckCards.pop_front();
           compHand_.append(m_deckCards[0]);
           m_deckCards.pop_front();

           setyTurn(true);
       }else{
           qDebug()<<"comp picks 1";
           compCards_.append("qrc:/Cards/back.png");
           setCompCards(compCards_);

           compHand_.append(m_deckCards[0]);
           m_deckCards.pop_front();

           setyTurn(true);
       }
    }

}

void GameManager::setrankList(QStringList top)
{
    topNames = top;
    emit rankListChanged();
}

void GameManager::playCard(QString card)
{
    setyTurn(false);
    setStackCard(card);
    emit computer();
}

void GameManager::deckPick(int num)
{
    qDebug()<<myHand_;
    myHand_.append(m_deckCards[0]);
    m_deckCards.pop_front();
    setMyHand(myHand_);
    qDebug()<<myHand_;
    if(num == 1){
        emit computer();
    }
}


void GameManager::setRoomlobbycode(QString lobbycode)
{
    if(m_roomLobbyCode != lobbycode){

        m_roomLobbyCode=lobbycode;
        emit roomlobbycodeChanged();
    }
}

void GameManager::setClientsInLobby(QStringList clientList)
{
    if(m_clientsInLobby != clientList){
        m_clientsInLobby=clientList;
        emit clientsInLobbyChanged();
    }
}

void GameManager::setDealtCards(QStringList dealtCards)
{
    m_messageHanlder->clientHand  = dealtCards;
    emit dealtCardsChanged();
}

void GameManager:: setYourTurn(bool turn){
    m_messageHanlder->yourTurn = turn;
    emit yourTurnChanged();
}

void GameManager::setNewStackCard(QString card)
{
     m_messageHanlder->stackCard = card;
     emit newStackCardChanged();
}
void GameManager::setNewDeckCard(QString card)
{
     m_messageHanlder->deckCard = card;
     emit newDeckCardChanged();
}

void GameManager::setOppCards(QStringList list)
{
    m_messageHanlder->oppCards = list;
    emit oppCardsChanged();
}

void GameManager::setPickNumber(QString num)
{
    m_messageHanlder->pickNum = num;
    emit pickNumberChanged();
}

void GameManager::setoppWonGame(bool opp)
{
    m_messageHanlder->oppWon_ = opp;
    emit oppWonGameChanged();
}

void GameManager::processSocketMessage(QString message)
{
    m_messageHanlder->processMessage(message);
}

void GameManager::registerUniqueID(QString uniqueID)
{
    qDebug()<<"ClientApp registering: "+uniqueID;
    m_clientID=uniqueID;
}

void GameManager::setMyHand(QStringList hand)
{
    myHand_ = hand;
    emit stackCardChanged();
}

void GameManager::setCompHand(QStringList hand)
{
    compHand_ = hand;
    emit compHandChanged();
}

void GameManager::lobbyJoined(QString lobbyID,QStringList clients)
{
    setRoomlobbycode(lobbyID);
    setClientsInLobby(clients);
    emit inGameLobby();
}

void GameManager::newClientReadyList(QStringList clientReadyList)
{
    if(m_readyClientList != clientReadyList){
        m_readyClientList=clientReadyList;
        emit readyListChanged();
    }
}

void GameManager::setStackCard(QString card)
{
    stackCard_ = card;
    emit stackCardChanged();
}

void GameManager::setyTurn(bool turn)
{
    yTurn_ = turn;
    emit yTurnChanged();
}

void GameManager::setHave(bool doesHave)
{
    have_ = doesHave;
    emit haveChanged();
}

void GameManager::setCompCards(QStringList hand)
{
    compHand_ = hand;
    emit compCardsChanged();
}


