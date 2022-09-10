import QtQuick 2.0

Rectangle {
    id:gameButton
    property string buttonColor: "#746AB0"
    property string buttonPressedColor: "#433885"
    property string buttonText: ""
    property  int  buttonTextPixelSize : 48

    signal buttonClicked()

    radius: 5
    color: buttonColor
    Text {
        anchors.centerIn: parent
        color: "black"
        text: buttonText
        font.pixelSize: buttonTextPixelSize
    }

    MouseArea{
        anchors.fill:parent
        onPressed: gameButton.color = buttonPressedColor
        onReleased: gameButton.color = buttonColor
        onClicked: gameButton.buttonClicked()
    }
}
