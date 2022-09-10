#include "websockethandler.h"

WebSocketHandler::WebSocketHandler(QObject *parent)
    : QObject{parent}
{
    m_webSocket = new QWebSocket();
    connect(m_webSocket,&QWebSocket::connected,this,&WebSocketHandler::onConnected);
    connect(m_webSocket,&QWebSocket::textMessageReceived,this,&WebSocketHandler::onTextMessageRecieved);

}

WebSocketHandler::~WebSocketHandler(){
    m_webSocket->deleteLater();
}

void WebSocketHandler::connectToServer(QString hostAddress)
{
    qDebug()<<"Client App: Connecting to server "<< hostAddress;
    m_webSocket->open(hostAddress);
}

void WebSocketHandler:: onTextMessageRecieved(QString message){

    qDebug()<<"Client App: Recieved message: "<<message;
    emit newMessageReadyForProcessing(message);
}

void WebSocketHandler::sendMessageToServer(QString message)
{
    m_webSocket->sendTextMessage(message);
}

void WebSocketHandler::onConnected()
{
    qDebug()<<"Client App: Connected to server";
   // m_webSocket->sendTextMessage("type:creategame;payload:0;sender:5555");

}
