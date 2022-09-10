import QtQuick 2.0

Item {

    Rectangle{
        id:backgroud
        anchors.fill: parent
        color: "#751467"

    }
    Text {
            id: titleText
            font.pixelSize: 72
            font.bold: true
            anchors {
                top: parent.top
                topMargin: 100
                left: parent.left
                leftMargin: 300
            }
            color: "white"
            text: "UNO!!!!<br>you win!..."
            horizontalAlignment: Text.AlignHCenter
        }
    Rectangle{
        id:messageWindowBackround
        radius: 5
        height: 40
        color: "#A4A9AD"
        anchors{
            left: titleText.left
            right: titleText.right
            rightMargin: 20
            top:titleText.bottom
            topMargin: 50
        }
    }
    TextEdit{
        id:messageWindow
        anchors.fill: messageWindowBackround
        font.pixelSize: 24
        readOnly: true
    }
    TextInput{
        id:textInputField
        anchors.fill:messageWindowBackround
        anchors.leftMargin: 5
        font.pixelSize: 25
        clip:true
        verticalAlignment: TextEdit.AlignVCenter
        onAccepted: {
            gameManager.writeFile("rank.txt",textInputField.text)
            textInputField.text =""
        }
    }

    GameButton{
        id:sendTextButton
        buttonText: "Send"
        buttonTextPixelSize: 40
        color: buttonColor
        width:170
        anchors{
            left:messageWindowBackround.right
            leftMargin: 20
            top:messageWindowBackround.top
            bottom: messageWindowBackround.bottom
        }
        onButtonClicked:{
            gameManager.writeFile("rank.txt",textInputField.text)
            textInputField.text =""
            gameManager.readFile("rank.txt")
            mainLoader.source = "qrc:/RankingScreen.qml"
        }
    }
}
