import QtQuick 2.0

Item {
    id: mainMenuScreen

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
        id:multiButton
        anchors.centerIn: parent
        buttonText: "Multiplayer"
        width: 300
        height: 80
        onButtonClicked: {
            webSocketHandler.connectToServer("ws://127.0.0.1:4001")
            mainLoader.source = "MultiPlayerSelectScreen.qml"
        }
    }
    GameButton{
        id:computerButton
        anchors{
           top: multiButton.bottom
           topMargin: 10
           horizontalCenter:parent.horizontalCenter
        }
        buttonText: "Vs Computer"
        width: 300
        height: 80
        onButtonClicked: mainLoader.source = "ComputerPlayerScreen.qml"

    }

    GameButton{
        id:quitButton
        anchors{
           top: computerButton.bottom
           topMargin: 10
           horizontalCenter:parent.horizontalCenter
        }

        buttonText: "Quit"
        width: 300
        height: 80
        onButtonClicked: Qt.quit()
    }
}

