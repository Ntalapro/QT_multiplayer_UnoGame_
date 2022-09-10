#include "messageprossecorhandler.h"
#include <QDebug>

MessageProssecorHandler::MessageProssecorHandler(QObject *parent)
    : QObject{parent}
{

}

void MessageProssecorHandler:: processMessage(QString message){

    //type:uniqueID;payload:5555
    //type:newLobbycreated;payload:1111;clientList:1111,2222,4444
    //type:joineSuccess;payload:1111;clientList:1111,2222,4444
    //type:updatedClientList;payload:1111,2222,4444
    //type:lobbyMessage;payload:message;sender:6666
    //type:lobbyreadyListChanged;payload:2222,3333,3444"
    //type:gameReadyToBegin;payload:0
    //type:fromDeckCard;payload:qrc:/Cards/0_b.png
    //type:newDeckCard;payload:qrc:/Cards/0_b.png
    //type:newStackCard;payload:qrc:/Cards/0_b.png
    //type:otherClientHandAdd;payload:0
    //type:otherClientHandSub;payload:0
    //type:PickNum;payload:4


        QStringList seperated = message.split( QRegExp(";"));

        if(seperated.first() == "type:uniqueID"){


            seperated.pop_front();
            if(seperated.first().contains("payload:")){

                QString newClientID = seperated.first();
                newClientID = newClientID.remove("payload:");
                emit uniqueIDRegistration(newClientID);

            }
        }
        else if(seperated.first() == "type:newLobbycreated" || seperated.first() == "type:joinSuccess"){
           // qDebug()<<"client app: new lobby created ";
            bool turn;
            if(seperated.first() == "type:newLobbycreated")
                 turn = true;
            if(seperated.first() == "type:joinSuccess")
                 turn = false;
            seperated.pop_front();
            QString lobbyID = QString();
            QStringList lobbyClients = QStringList();

            if(seperated.first().contains("payload:")){
                lobbyID = seperated.first();
                lobbyID = lobbyID.remove("payload:");
            }
            seperated.pop_front();
            if(seperated.first().contains("clientList:")){
                QString clients = seperated.first();
                clients = clients.remove("clientList:");
                lobbyClients = clients.split(QRegExp(","));
            }
            //qDebug()<<"Client App: LobbyClients => "<<lobbyClients;
            if(lobbyID != QString() && lobbyClients != QStringList()){
                emit turnChanged(turn);
                emit newLobby(lobbyID,lobbyClients);
            }

        }
        else if(seperated.first() =="type:updatedClientList"){

            //qDebug()<<"Client app: received new client update";
            seperated.pop_front();
            QString payload = seperated.first();
            payload = payload.remove("payload:");

            emit lobbyListUpdated( payload.split(QRegExp(",")));

        }
        else if(seperated.first() =="type:lobbyMessage"){
            //type:lobbyMessage;payload:message;sender:6666
            //senderID: message
           QString senderID;
           QString newMessage;
           seperated.pop_front();
           if(seperated.first().contains("payload:")){
               newMessage = seperated.first();
               newMessage = newMessage.remove("payload:");
           }
           seperated.pop_front();
           if(seperated.first().contains("sender:")){
               senderID = seperated.first();
               senderID = senderID.remove("sender:");
            }

           QString displayMessage(senderID +": "+newMessage);
           emit newLobbyMessage(displayMessage);
        }
        else if(seperated.first() =="type:lobbyreadyListChanged"){
            seperated.pop_front();
            QString payload = QString();
            if(seperated.first().contains("payload:")){
                payload = seperated.first();
                payload = payload.remove("payload:");
            }
            emit lobbyReadyListChanged(payload.split(QRegExp(",")));

        }
        else if(seperated.first() =="type:gameReadyToBegin"){
            emit gameStarting();
        }
        else if(seperated.first() =="type:fromDeckCard"){
            //type:fromDeckCard;payload:qrc:/Cards/0_b.png,qrc:/Cards/0_b.png,qrc:/Cards/0_b.png,
            QString cardLocation = QString();
            clientHand.pop_front();

             seperated.pop_front();
             if(seperated.first().contains("payload:")){
                 cardLocation = seperated.first();
                 cardLocation = cardLocation.remove("payload:");
                 qDebug()<<cardLocation;
             }
             clientHand = cardLocation.split( QRegExp(","));
             emit cardsDealt(clientHand);
             qDebug()<<clientHand;
        }else if(seperated.first() =="type:newDeckCard"){
            //type:newDeckCard;payload:qrc:/Cards/0_b.png
            //bool turn1 = true;

             seperated.pop_front();
             if(seperated.first().contains("payload:")){
                 deckCard = seperated.first();

                 deckCard = deckCard.remove("payload:");
             }
             //qDebug()<<deckCard;
             emit deckCardChanged(deckCard);
             //emit turnChanged(turn1);
        }
        else if(seperated.first() =="type:newStackCard"){
                    //type:newStackCard;payload:qrc:/Cards/0_b.png


                     seperated.pop_front();
                     if(seperated.first().contains("payload:")){
                         stackCard = seperated.first();
                         stackCard = stackCard.remove("payload:");
                     }
                     //qDebug()<<stackCard;
                     if(stackCard[11] == "d"){

                         pickNum = "2";
                         qDebug()<<"picknum = "<<pickNum;
                         emit pickNumChanged_(pickNum);
                     }
                     else if(stackCard[11] == "w"){


                         pickNum="4";
                         qDebug()<<"picknum = "<<pickNum;
                         emit pickNumChanged_(pickNum);
                     }
                     else{

                            pickNum="0";
                            qDebug()<<"picknum = "<<pickNum;
                         emit pickNumChanged_(pickNum);
                     }
                     emit stackCardChanged(stackCard);

        }else if(seperated.first() =="type:otherClientHandAdd"){
            //type:otherClientHandAdd;payload:0
            bool turn1 = true;
            oppCards.append("qrc:Cards/back.png");
            emit oppCardsChanged(oppCards);
            emit turnChanged(turn1);

        }
        else if(seperated.first() =="type:otherClientHandSub"){
                    //type:otherClientHandSub;payload:0
                bool turn1 = true;
                oppCards.pop_front();
                emit oppCardsChanged(oppCards);
                emit turnChanged(turn1);
        }
        else if(seperated.first() =="type:PickNum"){
            //type:PickNum;payload:4
            pickNum = seperated.back();
            pickNum = pickNum.remove("payload:");
            qDebug()<<"picknum = "<<pickNum;
            emit pickNumChanged_(pickNum);
        }else if(seperated.first() =="type:oppWon"){
            //type:oppWon;payload:0
            oppWon_ = true;
            emit oppWon(oppWon_);
        }
}
