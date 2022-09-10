import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    width: 1280
    height: 720
    visible: true
    title: qsTr("UnoLite Game Client")


    Connections{
        target: gameManager
        onInGameLobby : mainLoader.source = "qrc:/LobbyScreen.qml"
        onGameStarting: mainLoader.source = "qrc:/MultiPlayScreen.qml"
    }

    Loader{
        id: mainLoader
        anchors.fill: parent
        source: "qrc:/MainMenuScreen.qml"
    }
}
