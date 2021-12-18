import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.4
import Qt.labs.folderlistmodel 2.1

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    property alias swipeView: swipeView
    title: "Robot Control Program"

    property int index_old: 0

    SwipeView {
        id: swipeView
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent

        currentIndex: 0

        Connections {
            target: appCore // Указываем целевое соединение
            onSendToQml: {
               // textArea.text = count
            }
        }

        Item {
            id: firstPage

            Button {
               id: butBack
               x: 4
               y: 0
               width: 250
               height: 40
               text: "..."

               Image {
                   width: 40
                   height: 40
                   fillMode: Image.PreserveAspectFit
                   source:  "icons/folder.png"
               }

               onDoubleClicked: dataModel.folder = dataModel.parentFolder

               background: Rectangle {}
            }

            ListView {
                id: listView
                x: 0
                y: 40
                width: parent.width
                height: 300
                clip: true

                model: FolderListModel{
                    id: dataModel
                    showDirs: true
                    showDirsFirst: true
                    showFiles: true
                    folder: "file:///D://TEST_fILE"  //"file:///home/yastrebov/QT_Project/Control_Robot/Control_Robot_Program/Dir/Program/"
                    nameFilters: ["*.*"]
                }

                delegate: Item {
                    x: 5
                    width: 80
                    height: 55

                    Button{
                        id:bt_test
                        width: 200 + fileName.length * 6
                        height: 40
                        text: fileName
                        focus: true

                        onDoubleClicked: {
                            if (fileIsDir) {
                                dataModel.folder = fileURL
                            }
                        }
//                            background: Rectangle {
//                                id: rec_test
//                                color: bt_test.down && index_old!=index ? "#eeeded" : "white"

//                                onColorChanged: {
//                                    index_old=index
//                                }
//                            }

//                            onClicked: {
//                                 rec_test.forceActiveFocus()
//                            }

//                            onDownChanged: {
                            //        rec_test.forceActiveFocus()

//                                if(!this.activeFocus){
//                                     this.forceActiveFocus()
//                                }
//                            }
                    }

                    Image {
                        width: 40
                        height: 40
                        fillMode: Image.PreserveAspectFit
                        source:  fileIsDir ? "icons/folder.png" : "icons/file.png"
                    }


//                    onActiveFocusChanged: {
//                       //  bt_test.forceActiveFocus()
//                    }
                }

                highlight: Rectangle {
                    color: 'grey'
                }
            }

            Button {
                id: button
                x: 17
                y: 508
                width: 155
                height: 48
                text: qsTr("Создать программу")
                flat: false
                autoRepeat: false

                onClicked: {
                    appCore.createFile("D:\\TEST_fILE\\TEST_CREATE_FILE.txt", "Hello TEXT");
                }
            }

            Button {
                id: button1
                x: 182
                y: 508
                width: 160
                height: 48
                text: qsTr("Удалить программу")

                onClicked: {
                    appCore.deleteFile("D:\\TEST_fILE\\TEST_CREATE_FILE.txt");
                }
            }

            Button {
                id: button2
                x: 354
                y: 508
                width: 235
                height: 48
                text: qsTr("Отредактировать программу")
            }

            Button {
                id: button3
                x: 604
                y: 508
                width: 175
                height: 48
                text: qsTr("Запустить программу")
            }
        }

        // вторая вкладка SwipeView
        Item {
            id: secondPage
            Rectangle {
                id: rectangle
                x: 10
                y: 34
                width: 777
                height: 345
                color: "#ffffff"
                border.color: "black"

                TextArea {
                    id: textArea
                    anchors.rightMargin: 0
                    anchors.leftMargin: 0
                    anchors.topMargin: 1
                    anchors.bottomMargin: -1
                   // placeholderText: qsTr("Text Area")
                    anchors.fill: parent
                }

            }

            Rectangle {
                id: rectangle_2
                x: 10
                y: 418
                width: 777
                height: 84
                color: "#ffffff"
                border.color: "black"

                TextArea {
                    id: textArea_2
                    anchors.bottomMargin: 0
                    anchors.leftMargin: 0
                    anchors.topMargin: 0
                    anchors.rightMargin: 0
                    //placeholderText: qsTr("Text Area")
                    anchors.fill: parent
                }
            }

            Label {
                id: label
                x: 10
                y: 390
                text: qsTr("Аварийные и информационные сообщения:")
            }

            Label {
                id: label1
                x: 10
                y: 11
                width: 271
                height: 17
                text: qsTr("Листинг программы робота:")
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
