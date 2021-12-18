import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.4
import Qt.labs.folderlistmodel 2.1


ApplicationWindow {
    visible: true
    width: 648
    height: 488
    title: "Test Swipe"

    SwipeView {
        id: swipeView
        anchors.rightMargin: 6
        anchors.bottomMargin: 8
        anchors.leftMargin: -6
        anchors.topMargin: -8
        anchors.fill: parent
        currentIndex: 0

        Connections {
            target: appCore // Указываем целевое соединение
            onSendToQml: {
                labelCount.text = count // Устанавливаем счётчик в текстовый лейбл
            }
        }

        Item {
            id: firstPage
            Text {
                id: name1
                anchors.centerIn:  parent
                text: button.down ? qsTr("Нажата кнопка старт") : qsTr("Кнопка старт не нажата")
                font.family: "Arial"
                font.pointSize: 24
            }
            Text {
                id: labelCount
                x: 75
                y: 150
                text:  qsTr("0")
                font.family: "Arial"
                font.pointSize: 24
            }


            Button {
                id: button
                x: 50
                y: 50
                text: qsTr("Start")
                background: Rectangle {
                    color: button.down ? "red" : "#21be2b"
                    implicitWidth: 100
                    implicitHeight: 40
                    opacity: enabled ? 1 : 0.3
                    border.color: "black"
                    border.width: 1
                    radius: 2
                }

                onClicked: {
                    appCore.receiveFromQml()
                }
            }

            Button {
                id: button3
                x: 200
                y: 50
                text: qsTr("Stop")

                background: Rectangle {
                    color: button3.down ? "red" : "#21be2b"
                    implicitWidth: 100
                    implicitHeight: 40
                    opacity: enabled ? 1 : 0.3
                    border.color: "black"
                    border.width: 1
                    radius: 2
                }
                onClicked: {
                    appCore.testMetod()
                }
            }
        }

        Item {
            id: secondPage
            Text {
                id: name3
                anchors.centerIn:  parent
                text: button2.down ? qsTr("Нажата кнопка стоп") : qsTr("Кнопка стоп не нажата")
                font.family: "Arial"
                font.pointSize: 24
            }
            Button {
                id: button2
                x: 50
                y: 50
                text: qsTr("Stop")

                background: Rectangle {
                    color: button2.down ? "red" : "#21be2b"
                    implicitWidth: 100
                    implicitHeight: 40
                    opacity: enabled ? 1 : 0.3
                    border.color: "black"
                    border.width: 1
                    radius: 2
                }
                onClicked: {
                    appCore.testMetod()
                }
            }
        }

}
    PageIndicator {
        id: indicator

        count: swipeView.count
        currentIndex: swipeView.currentIndex

        anchors.bottom: swipeView.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }

}
