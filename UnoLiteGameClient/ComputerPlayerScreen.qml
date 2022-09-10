import QtQuick 2.0

Item {
    id: computerPlayerScreen
    property var compCards: gameManager.compCards
    property var myhandCards: gameManager.myHand
    property var compHand2: gameManager.compHand
    property string stackCard: gameManager.stackCard
    property int count: 0
    property bool yTurn: gameManager.yTurn
    property bool dontHave: gameManager.have
    property string picked: ""
    property int pickcard2_4: 1

    onStackCardChanged:switch(stackCard[11]){
                            case "d":
                                pickcard2_4 =2
                                count =0
                                break;
                            case"w":
                                pickcard2_4 = 4
                                count =0
                                break;
                            default:
                                  pickcard2_4 = 1
                                  count = 0

                            }
    onMyhandCardsChanged:if(pickcard2_4 !== 1){
                              pickcard2_4--
                              myHand.model = myhandCards
                          }else{
                                  myHand.model = myhandCards

                              }



    Rectangle{
        id:backgroud
        anchors.fill: parent
        color: "#751467"

    }
    //#dfe2e6
    Rectangle{
        id:computerCardsBackround
        radius: 5
        color: "#a2a8b0"
        width: parent.width - 10
        height: 150
        anchors{
            top:parent.top
            topMargin: 20
            horizontalCenter: parent.horizontalCenter
        }
    }

    ListView{
        id:computerHand
        model: compCards
        orientation: ListView.Horizontal
        delegate: Image{
                id:compCardImage
                source: modelData
                visible: true
                width:100
                height:130
                fillMode: Image.PreserveAspectFit
            }
        anchors.horizontalCenter: computerCardsBackround.horizontalCenter
        anchors.fill: computerCardsBackround
        anchors.topMargin: 10
    }

    Rectangle{
        id:deck_stack_CardsBackround
        radius: 5
        color: "#a2a8b0"
        width: parent.width - 10
        height: 150
        anchors{
            top:computerCardsBackround.bottom
            topMargin: 15
            horizontalCenter: parent.horizontalCenter
        }
    }
    Image{
           id:deckImage
           source: "qrc:/Cards/deck.png"
           visible: true
           width:100
           height:130
           fillMode: Image.PreserveAspectFit
           anchors{
               top: deck_stack_CardsBackround.top
               right: deck_stack_CardsBackround.right
               topMargin: 10
               rightMargin: 240
           }
           MouseArea{
               anchors.fill: parent
               onClicked: {

                   if(yTurn === true){
                       gameManager.deckPick(pickcard2_4)
                       myHand.model = myhandCards

                   }
               }
           }
    }
    Image{
           id:stackImage
           source:stackCard
           visible: true
           width:100
           height:130
           fillMode: Image.PreserveAspectFit
           anchors{
               top: deck_stack_CardsBackround.top
               left: deck_stack_CardsBackround.left
               topMargin: 10
               leftMargin: 240
           }
    }

    Rectangle{
        id:myCardsBackround
        radius: 5
        color: "#a2a8b0"
        width: parent.width - 10
        height: 150
        anchors{
            top:deck_stack_CardsBackround.bottom
            topMargin: 15
            horizontalCenter: parent.horizontalCenter
        }
    }
    ListView{
        id:myHand
        model: myhandCards
        orientation: ListView.Horizontal
        delegate: Image{
                id:mycardImage
                source: modelData
                visible: true
                width:100
                height:130
                fillMode: Image.PreserveAspectFit
                MouseArea{
                    anchors.fill: parent
                    function change(){
                        gameManager.playCard(mycardImage.source)
                        myhandCards.splice(index,1)
                        myHand.model = myhandCards
                    }
                    onClicked: {

                    if(yTurn == true){
                        picked = mycardImage.source
                        if(stackCard.length === 18){
                            switch(picked.length) {
                              case 18:
                                if(stackCard.includes(picked[11],11) ||
                                        stackCard.includes(picked[13],11)){
                                    change()

                                }
                                break;
                              case 19:
                                  if(stackCard.includes(picked[14],11)){
                                     change()

                                  }
                                  break;
                            }
                        }else{
                            switch(picked.length) {
                              case 18:
                                if(stackCard.includes(picked[13],11)){
                                    change()
                                  //  gameManager.compTurn()

                                }
                                break;
                              case 19:
                                  if(stackCard.includes(picked[12],11)
                                          || stackCard.includes(picked[14],13)){
                                     change()
                                     // gameManager.compTurn()

                                  }
                                  break;
                            }
                        }
                    }
                  }
                }
            }
        anchors.horizontalCenter: myCardsBackround.horizontalCenter
        anchors.fill: myCardsBackround
        anchors.topMargin: 10
    }

}

