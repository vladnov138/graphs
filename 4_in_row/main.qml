import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    ColumnLayout {
        id: layout
        anchors.fill: parent
        spacing: 10

        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: 20

            Button {
                text: "Restart Game"
                onClicked: {
                    gameController.restartGame();
                }
            }

            Text {
                id: gameStatus
                text: "Game in progress"
                font.pointSize: 16
                color: "blue"
                Layout.alignment: Qt.AlignHCenter

                Connections {
                    target: gameController
                    onUpdateGameStatus: {
                        if (gameOver) {
                            gameStatus.text = isPlayerWin ? "Game over. Human win!" : "Game over. AI win!"
                            gameBoard.opacity = 0.5
                        } else {
                            gameStatus.text = "Game in progress"
                            gameBoard.opacity = 1
                        }
                    }
                }
            }
        }

        GridLayout {
            id: gameBoard
            columns: 7
            rowSpacing: 5
            columnSpacing: 5
            Layout.alignment: Qt.AlignHCenter

            Repeater {
                model: 6 * parent.columns
                Rectangle {
                    id: cell
                    width: 60
                    height: 60
                    // color: board[Math.floor(index / columns)][index % columns] === 0 ? "lightgray" :
                    //        board[Math.floor(index / columns)][index % columns] === 1 ? "red" : "yellow"
                    border.color: "black"
                    border.width: 2
                    radius: 30

                    required property int index

                    property int row: Math.floor(index / columns)
                    property int column: columns

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            let player = gameController.makeMove(index);
                            if (player > 0) {
                                parent.color = player === 1 ? "red" : "yellow";
                            }
                        }
                    }

                    Connections {
                        target: gameController
                        onCellUpdated: {
                            if (index === cell.index) {
                                switch (player) {
                                case 1:
                                    cell.color = "red";
                                    break;
                                case 2:
                                    cell.color = "yellow";
                                    break;
                                default:
                                    cell.color = "white";
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
