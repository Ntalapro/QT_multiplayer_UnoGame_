#include "websockethandler.h"
#include <QDebug>
#include <random>
#include <QDateTime>

WebSocketHandler::WebSocketHandler(QObject *parent)
    : QObject{parent}
{
  m_socketserver = new QWebSocketServer("UnoLiteServer",QWebSocketServer::NonSecureMode, this);

  connect(m_socketserver,&QWebSocketServer::newConnection,this,&WebSocketHandler::onNewSocketConnection);

  if(m_socketserver->listen(QHostAddress::Any, 4001)){
      qDebug() <<"Server running on port 4001";
  }
  else{
        qDebug()<<"Server not running";
  }

}

WebSocketHandler::~WebSocketHandler()
{
    m_socketserver->deleteLater();
}

void WebSocketHandler::sendTextMessageToClient(QString message, QString clientID)
{
    if(m_clientlist.contains(clientID)){
        QWebSocket *existingClient = m_clientlist[clientID];
        existingClient->sendTextMessage(message);
    }
}

void WebSocketHandler::sendTextMessageToMultipleClients(QString message, QStringList clientIDS)
{
    foreach(const QString & client,clientIDS){
        sendTextMessageToClient(message,client);
    }
}

void WebSocketHandler:: onNewSocketConnection(){

    std::default_random_engine generator;
    generator.seed(QDateTime::currentMSecsSinceEpoch());

    std::uniform_int_distribution<int> idGenerator(1000,9999);
    QString newClientID = QString::number(idGenerator(generator));

    while(m_clientlist.keys().contains(newClientID)){
        newClientID = QString::number(idGenerator(generator));
    }

    auto nextClient = m_socketserver->nextPendingConnection();
    nextClient -> setParent(this);

    connect(nextClient,&QWebSocket::textMessageReceived,this,&WebSocketHandler::onTextMessageRecieved);
    connect(nextClient,&QWebSocket::disconnected,this,&WebSocketHandler::onSocketDsiconnected);

    nextClient->sendTextMessage("type:uniqueID;payload:" + newClientID);

    m_clientlist[newClientID ]=nextClient;

    qDebug() << "new client connected!";



}

void WebSocketHandler::onTextMessageRecieved(QString message)
{
    qDebug()<<"Server recieved: new Client text: "<<message;
    emit newMessageToProcess(message);

}

void WebSocketHandler::onSocketDsiconnected()
{
    auto client = qobject_cast<QWebSocket*>(sender());

    if(client){
        for(QMap<QString,QWebSocket*>::iterator mapIterator = m_clientlist.begin();
            mapIterator!=m_clientlist.end();
            mapIterator++){

            if(mapIterator.value() == client){
                QString uid = mapIterator.key();
                m_clientlist.remove(uid);
                client->deleteLater();
            }
        }
    }

    qDebug() <<"Client Disconnected: "<< client->peerPort();
}
