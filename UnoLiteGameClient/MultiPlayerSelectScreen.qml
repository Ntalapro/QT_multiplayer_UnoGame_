import QtQuick 2.0

Item {
    id: gameSelectScreen

    Rectangle{
        id:backgroud
        anchors.fill: parent
        color: "#751467"

    }

    Text{
        id:titleText
        font.pixelSize: 72
        font.bold: true
        anchors{
            top:parent.top
            topMargin: 40
            horizontalCenter: parent.horizontalCenter
        }
        color: "black"
        text: "UnoLite"
    }

    GameButton{
        id:createGameButton
        anchors{
            top: titleText.bottom
            topMargin: 70
            horizontalCenter: parent.horizontalCenter
        }

        buttonText: "Create Game"
        buttonTextPixelSize: 48
        width: 300
        height: 90
        onButtonClicked: gameManager.createGameRequest()
    }
    GameButton{
        id:joinButton
        anchors{
           top: createGameButton.bottom
           topMargin: 20
           horizontalCenter:parent.horizontalCenter
        }

        buttonText: "Join Game"
        buttonTextPixelSize: 48
        width: 300
        height: 90
        onButtonClicked: mainLoader.source = "JoinLobbyScreen.qml"
    }
    GameButton{
        id:backButton
        anchors{
           top: joinButton.bottom
           topMargin: 20
           horizontalCenter:parent.horizontalCenter
        }

        buttonText: "Back"
        buttonTextPixelSize: 48
        width: 300
        height: 90
        onButtonClicked: mainLoader.source = "MainMenuScreen.qml"
    }
}
