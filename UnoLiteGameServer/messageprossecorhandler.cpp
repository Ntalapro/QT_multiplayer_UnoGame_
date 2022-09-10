#include "messageprossecorhandler.h"
#include "qdebug.h"

MessageProssecorHandler::MessageProssecorHandler(QObject *parent)
    : QObject{parent}
{

}

void MessageProssecorHandler::processMessage(QString message)
{
    //qDebug()<<"Server App: Message to process: "<<message;
    //type:creategame;payload:0;sender:5555
    //type:joingame;payload:4000;sender:5555
    //type:message;payload:helloworld;lobbyID:5555;sender:5555
    //type:readyToPlay:payload:1;sender:6564
    //type:cardClicked;payload:qrc:/Cards/0_b.png;sender:6675
    //type:deckClicked;sender:7574;pick:2
    //type:won;sender:3435

    QStringList seperated = message.split( QRegExp(";"));

    if(seperated.first() == "type:creategame"){
        qDebug()<<"Create Game request";
        seperated.pop_front();
        seperated.pop_front();
        if(seperated.first().contains("sender:")){
            QString senderID = seperated.first();
            senderID = senderID.remove("sender:");
            emit createGameRequest(senderID);
        }
    }else if(seperated.first() == "type:joingame"){
        qDebug()<<"join game request";
        seperated.pop_front();
        QString lobbyID = QString();
        QString senderID = QString();
        if(seperated.first().contains("payload:")){
            lobbyID = seperated.first();
            lobbyID = lobbyID.remove("payload:");

        }
        seperated.pop_front();
        if(seperated.first().contains("sender:")){
            senderID = seperated.first();
            senderID = senderID.remove("sender:");

        }

        if( lobbyID != QString() && senderID != QString() )
            emit joinGameLobbyRequest(lobbyID,senderID);

    }else if(seperated.first() == "type:message"){
        // type:message;payload:message;lobbyID:5555;sender:5555
         qDebug()<<"lobby message request";
         QString payload = QString();
         QString lobbyID = QString();
         QString senderID = QString();

         seperated.pop_front();
         if(seperated.first().contains("payload:")){
             payload = seperated.first();
             payload = payload.remove("payload:");

         }
         seperated.pop_front();
         if(seperated.first().contains("lobbyID:")){
             lobbyID = seperated.first();
             lobbyID = lobbyID.remove("lobbyID:");
         }
         seperated.pop_front();
         if(seperated.first().contains("sender:")){
             senderID = seperated.first();
             senderID = senderID.remove("sender:");

         }

         if( payload!=QString() &&& lobbyID != QString() && senderID != QString() )
            emit messageLobbyRequest(payload,lobbyID,senderID);

    }else if(seperated.first() == "type:readyToPlay"){
        if(seperated.back().contains("sender:")){
            QString clientID = seperated.back();
            clientID = clientID.remove("sender:");

            emit clientReadyToPlay(clientID);
        }
    }else if(seperated.first() == "type:cardClicked"){
    //type:cardClicked;payload:qrc:/Cards/0_b.png;sender:6675
        QString card = QString();
        QString senderID = QString();
        seperated.pop_front();
        if(seperated.first().contains("payload:")){
            card = seperated.first();
            card = card.remove("payload:");

        }
        senderID = seperated.back();
        senderID = senderID.remove("sender:");
        emit sendStackCard(card,senderID);

    }else if(seperated.first() == "type:deckClicked"){
        //type:deckClicked;sender:7574

        QString pickNum = QString();
        QString senderID = QString();

        pickNum = seperated.back();
        pickNum = pickNum.remove("pick:");
        seperated.pop_back();
        senderID = seperated.back();
        senderID = senderID.remove("sender:");

        emit sendDeckCard(senderID,pickNum);
    }else if(seperated.first() == "type:won"){
        //"type:won;sender:"+m_clientID
        QString senderID = QString();

        senderID = seperated.back();
        senderID = senderID.remove("sender:");
        emit sendWinner(senderID);
    }

}
