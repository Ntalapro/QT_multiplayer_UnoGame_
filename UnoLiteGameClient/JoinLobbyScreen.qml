import QtQuick 2.0
import QtQuick.Controls 2.0

Item {

    Rectangle{
        id:backgroud
        anchors.fill: parent
        color: "#751467"

    }

    Text{
        id:codetitleText
        font.pixelSize: 72
        font.bold: true
        anchors{
            top:parent.top
            topMargin: 15
            horizontalCenter: parent.horizontalCenter
        }
        color: "white"
        text: "Enter Game Code"
    }

    Rectangle{
        id:lobbyCodeTextFieldBackround
        radius: 5
        width : 500
        height:75
        color: "#A4A9AD"
        anchors.top: codetitleText.bottom
        anchors.topMargin : 60
        anchors.horizontalCenter:parent.horizontalCenter
    }
    TextEdit{
        id:joinLobbytextEditField
        anchors.fill:lobbyCodeTextFieldBackround
        font.pixelSize: 48
        font.bold: true
        clip:true
        horizontalAlignment:  Text.AlignHCenter
        verticalAlignment: Text.AlignHCenter

    }

    GameButton{
        id:joinLobbyButton
        anchors{
           top: lobbyCodeTextFieldBackround.bottom
           topMargin: 50
           horizontalCenter:parent.horizontalCenter
        }
        buttonText: "Join Game"
        buttonTextPixelSize: 36
        width: 200
        height: 75
        onButtonClicked:{
            // @disable-check M325
            if(joinLobbytextEditField !== ""){
                gameManager.joinGameRequest(joinLobbytextEditField.text)
            }
        }
    }
    GameButton{
        id:joinLobbybackButton
        anchors{
           top: joinLobbyButton.bottom
           topMargin: 10
           horizontalCenter:parent.horizontalCenter
        }
        buttonText: "Back"
        buttonTextPixelSize: 36
        width: 200
        height: 75
        onButtonClicked: mainLoader.source = "MainMenuScreen.qml"
    }


}
