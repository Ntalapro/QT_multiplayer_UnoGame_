import QtQuick 2.0

Item {
    id: multiPlayerScreen

    property var cards: gameManager.dealtCards
    property var oppCards: gameManager.oppCards
    property bool yourTurn: gameManager.yourTurn
    //property string add_sub : gameManager.add_sub
    property string deckCard_: gameManager.newDeckCard
    property string stackCard_: gameManager.newStackCard
    property bool dontHave: false
    property string picked: ""
    property string pickNumber: gameManager.pickNumber
    property bool oppWon: gameManager.oppWonGame
    onOppWonChanged: if(oppWon===true){
                         mainLoader.source = "OppWonScreen.qml"
                     }
    onCardsChanged: if(cards.length === 0){
                        gameManager.winner()
                        mainLoader.source = "qrc:/WinScreen.qml"
                    }

    /*function add_or_sub() {
        if(add_sub === "add"){
            oppCards.push("qrc:Cards/back.png")
        }else if(add_sub === "sub"){
            oppCards.splice(0,1)
        }
        return oppCards
    }*/

    Rectangle{
        id:backgroud
        anchors.fill: parent
        color: "#5b4475"

    }
    Rectangle{
        id:opponetCardsBackround
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
        id:opponentHand
        model: oppCards
        orientation: ListView.Horizontal
        delegate: Image{
                id:oppCards_Image
                source: modelData
                visible: true
                width:100
                height:130
                fillMode: Image.PreserveAspectFit
            }

        anchors.horizontalCenter: opponetCardsBackround.horizontalCenter
        anchors.fill: opponetCardsBackround
        anchors.topMargin: 10
    }


    Rectangle{
        id:deck_stack_CardsBackround
        radius: 5
        color: "#a2a8b0"
        width: parent.width - 10
        height: 150
        anchors{
            top:opponetCardsBackround.bottom
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
                   if(yourTurn === true){
                       if(pickNumber === "4"){
                           gameManager.deckCardClicked("3",true)
                           cards.push(gameManager.newDeckCard)
                       }else if(pickNumber === "3"){
                           gameManager.deckCardClicked("2",true)
                           cards.push(gameManager.newDeckCard)
                       }else if(pickNumber === "2"){
                           gameManager.deckCardClicked("1",true)
                           cards.push(gameManager.newDeckCard)
                       }else if(pickNumber === "1"){
                           gameManager.deckCardClicked("0",false)
                           cards.push(gameManager.newDeckCard)
                       }else{
                           gameManager.deckCardClicked("0",false)
                           cards.push(gameManager.newDeckCard)
                       }

                   }

               }
           }
    }
    Image{
           id:stackImage
           source: stackCard_
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
        id:myCards
        model: cards
        orientation: ListView.Horizontal
        delegate: Image{
                id:myCards_image
                source: modelData
                visible: true
                width:100
                height:130
                fillMode: Image.PreserveAspectFit
                function change(){
                    gameManager.cardClicked(myCards_image.source,false)
                    cards.splice(index,1)
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        if(yourTurn === true){
                            picked = myCards_image.source

                            if(stackCard_.length === 18){
                                //pickcard2_4 = 0;
                                switch(picked.length) {
                                  case 18:
                                    if(stackCard_.includes(picked[11],11) ||
                                            stackCard_.includes(picked[13],11)){
                                        change()

                                    }
                                    break;
                                  case 19:
                                      if(stackCard_.includes(picked[14],11)){
                                         change()
                                      }
                                      break;
                                }
                            }
                                switch(picked.length) {
                                  case 18:
                                      //qrc:/Cards/7_b.png
                                    if(stackCard_.includes(picked[13],11)){
                                        change()
                                    }

                                    break;
                                  case 19:
                                      if(stackCard_.includes(picked[12],11)
                                              || stackCard_.includes(picked[14],13)){
                                         change()
                                      }
                                      break;
                                }
                            }
                        }

                    }
                }

        anchors{
            fill: myCardsBackround
            horizontalCenter: myCardsBackround.horizontalCenter
            verticalCenter: myCardsBackround.verticalCenter
        }

    }

}
