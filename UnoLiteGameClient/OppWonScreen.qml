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
            text: "UNO!!!!<br>you lost!..."
            horizontalAlignment: Text.AlignHCenter
        }
    GameButton{
        id:sendTextButton
        buttonText: "Done"
        buttonTextPixelSize: 40
        color: buttonColor
        height: 50
        width:170
        anchors{
            top: titleText.bottom
            topMargin: 30
            horizontalCenter: parent.horizontalCenter
        }
        onButtonClicked:{
            //gameManager.writeFile("rank.txt",textInputField.text)
            //textInputField.text =""
            gameManager.readFile("rank.txt")
            mainLoader.source = "qrc:/RankingScreen.qml"
        }
    }

}
