import QtQuick 2.0

Item {

    property var rank: gameManager.rankList
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
            topMargin: 28
            horizontalCenter: parent.horizontalCenter
        }
        color: "black"
        text: "Ranking"
    }

    Rectangle{
        id:roomLobbyLsitBackround
        radius: 5
        color: "#A4A9AD"
        width: 300
        height: 300
        anchors{
            centerIn: parent
        }
    }

    ListView{
        id:roomLobbyList
        model: rank
        clip: true
        delegate: Text{
            id:userID
            anchors.horizontalCenter: parent.horizontalCenter
            text:modelData
            font.bold: true
            font.pixelSize: 36
            color: "white"
        }
        anchors.fill: roomLobbyLsitBackround
    }
}

