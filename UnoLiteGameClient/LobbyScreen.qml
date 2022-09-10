import QtQuick 2.0

Item {


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
            topMargin: 15
            horizontalCenter: parent.horizontalCenter
        }
        color: "white"
        text: "Lobby Code: "+ gameManager.roomlobbycode
    }

    Rectangle{
        id:roomLobbyLsitBackround
        radius: 5
        color: "#A4A9AD"
        width: 290
        height: 300
        anchors{
            top:titleText.bottom
            left: parent.left
            topMargin: 15
            leftMargin: 30
        }
    }
    ListView{
        id:roomLobbyList
        model: gameManager.clientsInLobby
        delegate: Text{
            id:userID
            anchors.horizontalCenter: parent.horizontalCenter
            text:modelData
            font.bold: true
            font.pixelSize: 36
            color: "white"

            Image{
                id:checkImage
                source: "qrc:/check.png"
                visible: gameManager.isClientReady(modelData)

                Connections{
                    target: gameManager
                    onReadyListChanged: checkImage.visible = gameManager.isClientReady(modelData)
                }

                anchors{
                    left: userID.right
                    leftMargin: 8
                    verticalCenter: userID.verticalCenter
                }

                width:35
                height:35
                fillMode: Image.PreserveAspectFit
            }
        }
        anchors.fill: roomLobbyLsitBackround
    }

    Rectangle{
        id:messageWindowBackround
        radius: 5
        color: "#A4A9AD"
        anchors{
            left: roomLobbyLsitBackround.right
            leftMargin: 10
            right: parent.right
            rightMargin: 20
            top:roomLobbyLsitBackround.top
            bottom: roomLobbyLsitBackround.bottom
        }
    }
    TextEdit{
        id:messageWindow
        anchors.fill: messageWindowBackround
        font.pixelSize: 24
        readOnly: true
    }
    Connections{
        target:gameManager
        onNewLobbyMessage: messageWindow.append(message)
    }


    Rectangle{
        id:sendTextFieldBackround
        radius: 5
        color: "#A4A9AD"
        anchors{
            left: messageWindowBackround.left
            right: sendTextButton.left
            rightMargin: 10
            top:sendTextButton.top
            bottom: sendTextButton.bottom
        }
    }
    TextInput{
        id:textInputField
        anchors.fill:sendTextFieldBackround
        anchors.leftMargin: 5
        font.pixelSize: 25
        clip:true
        verticalAlignment: TextEdit.AlignVCenter
        onAccepted: {
            gameManager.sendMessageToLobby(textInputField.text)
            textInputField.text =""
        }
    }

    GameButton{
        id:readybutton
        buttonText: "Ready"
        buttonTextPixelSize: 40
        anchors{
            left: roomLobbyLsitBackround.left
            right: roomLobbyLsitBackround.right
            top:roomLobbyLsitBackround.bottom
            topMargin: 15
            bottom: parent.bottom
            bottomMargin: 15
        }
        onButtonClicked: gameManager.readyToPlay()
    }
    GameButton{
        id:sendTextButton
        buttonText: "Send"
        buttonTextPixelSize: 40
        width:170
        anchors{
            right:messageWindowBackround.right
            top:readybutton.top
            bottom: readybutton.bottom
        }
        onButtonClicked:{
            gameManager.sendMessageToLobby(textInputField.text)
            textInputField.text =""
        }
    }
}
