import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.4
import Qt.labs.folderlistmodel 2.1
//import QtQuick.Dialogs 1.1

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: "Robot Control Program"
    color: "#4c4e50"

    //flags: Qt.FramelessWindowHint // Отключаем обрамление окна

    property alias swipeView: swipeView
    property string path: ""
    property string file: ""
    property string actTextProg: ""
    property int counAx1: 0
    property string actProgName: ""

    property int index_ext: 0
    property int index_ext_priv: 0
    property int tool_n: 1
    property int base_n: 1

    property bool newornot: false



    DialogNewPoint{id: dialogNPoint}

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
            onClearListMode: {
                 listModel.clear()
            }
            onInsertToListMode: {
                 listModel.append({name: " PTP " + name +" ",
                                     Tool: " Tool: "+ tool, Base: " Base: "+ base, Color: "#2e2f30", FontColor: "white"})
                 swipeView.currentIndex = 1
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

               Image {
                   width: 40
                   height: 40
                   fillMode: Image.PreserveAspectFit
                   source:  "icons/folder.png"
               }

               onDoubleClicked: dataModel.folder = dataModel.parentFolder

               flat: true
               autoRepeat: false

               contentItem: Text {
                   text: "..."
                   font: butBack.font
                   opacity: enabled ? 1.0 : 0.3
                   color: butBack.down ? "#4c4e50" : "white"
                   horizontalAlignment: Text.AlignHCenter
                   verticalAlignment: Text.AlignVCenter
                   elide: Text.ElideRight
               }

               background: Rectangle { color: "#4c4e50"}
            }

            ListView {
                id: listView
                x: 0
                y: 40
                width: parent.width
                height: 450
                clip: true

                model: FolderListModel{
                    id: dataModel
                    showDirs: true
                    showDirsFirst: true
                    showFiles: true
                    folder: "file:///home/xenomai/git/Robot_Control/Control_Robot_Program/Dir/Program"
                    nameFilters: ["*.*"]

                    onCountChanged: {
                       path = "/home/xenomai/git/Robot_Control/Control_Robot_Program/Dir/Program"
                    }
                }

                delegate:Component {
                    Item {
                    x: 5
                    width: parent.width
                    height: 45

                    Column {
                        Image {
                            width: 40
                            height: 40
                            fillMode: Image.PreserveAspectFit
                            source:  fileIsDir ? "icons/folder.png" : "icons/file.png"
                        }
                    }
                   Text {
                       id: textFile
                        x: 50
                        y: 15
                        text: fileName
                        color: "white"
                   }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            listView.currentIndex = index
                             if (!fileIsDir) {
                              file = fileName
                             }
                        }

                        onDoubleClicked: {
                            if (fileIsDir) {
                               dataModel.folder = fileURL
                                path = filePath
                            }
                        }
                    }

                }
              }
                highlight: Rectangle {
                    color: "#eeeded"
                }


            }

            Dialog {
                id: dialogCreate
                x: 250
                y: 250
                width: 350
                height: 150
                title: "Введите имя файла"
                modal: false
                standardButtons: Dialog.Ok | Dialog.Cancel

                TextField {
                    id: textField
                    width: 326
                    height: 30
                    font.family: "Arial"
                    font.pointSize: 12
                }

                onAccepted: {
                    if (textField.text != ""){
                        actProgName = textField.text
                        appCore.createFile(textField.text, path)
                    }
                }
            }


            Button {
                id: butCreateProg
                x: 52
                y: 510
                width: 155
                height: 48
                flat: true
                autoRepeat: false

                contentItem: Text {
                    text: qsTr("Создать программу")
                    font: butCreateProg.font
                    opacity: enabled ? 1.0 : 0.3
                    color: butCreateProg.down ? "#4c4e50" : "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }

                background: Rectangle {
                    anchors.fill: parent
                    border.color: "#008000"
                    color: butCreateProg.down ? "white" : "#4c4e50"
                    radius: 5
                }
                onClicked: {
                    dialogCreate.open() // открываем диалог для ввода имени файла и его создания
                }
            }

            Button {
                id: butDeleteProg
                x: 219
                y: 510
                width: 160
                height: 48
                flat: true
                autoRepeat: false

                contentItem: Text {
                    text: qsTr("Удалить программу")
                    font: butDeleteProg.font
                    opacity: enabled ? 1.0 : 0.3
                    color: butDeleteProg.down ? "#4c4e50" : "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }

                background: Rectangle {
                    anchors.fill: parent
                    border.color: "#008000"
                    color: butDeleteProg.down ? "white" : "#4c4e50"
                    radius: 5
                }
                onClicked: {
                    appCore.deleteFile(file, path);
                }
            }

            Button {
                id: butEditProg
                x: 391
                y: 510
                width: 168
                height: 48
                flat: true
                autoRepeat: false

                contentItem: Text {
                    text: qsTr("Отредактировать программу")
                    font: butEditProg.font
                    opacity: enabled ? 1.0 : 0.3
                    color: butEditProg.down ? "#4c4e50" : "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }

                background: Rectangle {
                    anchors.fill: parent
                    border.color: "#008000"
                    color: butEditProg.down ? "white" : "#4c4e50"
                    radius: 5
                }
                onClicked: {
//                    var readFromFile = appCore.readFromFile(path + "/"+ file)
//                    var splitText = readFromFile.split('\n');
//                    var textToFor = "";

//                    for(var i = 0; i < splitText.length; i++){
//                       textToFor +=  splitText[i]
//                       if(splitText[i]==="</font> "){

//                        }
//                    }

//                    actTextProg = ""
                    appCore.openFile(file, path)
                   // listModel.append({name: " PTP " + textNamePoint.text+" ",
                                 //        Tool: " Tool: "+ textNumTool.text, Base: " Base: "+ textNumBase.text, Color: "#2e2f30", FontColor: "white"})
                   // swipeView.currentIndex = 1
                }
            }

            Button {
                id: butStartProg
                x: 572
                y: 510
                width: 175
                height: 48
                flat: true
                autoRepeat: false

                contentItem: Text {
                    text: qsTr("Запустить программу")
                    font: butStartProg.font
                    opacity: enabled ? 1.0 : 0.3
                    color: butStartProg.down ? "#4c4e50" : "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }

                background: Rectangle {
                    anchors.fill: parent
                    border.color: "#008000"
                    color: butStartProg.down ? "white" : "#4c4e50"
                    radius: 5
                }
            }
        }

        // вторая вкладка SwipeView
        Item {
            id: secondPage
            ManualMoveModul{id: manualMoveModul}

            Rectangle {
                id: rectangle
                x: 10
                y: 34
                width: 659
                height: 324
                color: "#2e2f30"
                border.color: "black"

                // ListView для представления данных в виде списка
                ListView {
                    id: listView1
                    anchors.fill: parent

                    /* в данном свойстве задаём вёрстку одного объекта
                     * который будем отображать в списке в качестве одного элемента списка
                     * */
                    delegate: Item {
                        id: item_1
                        anchors.left: parent.left
                        anchors.right: parent.right
                        height: 25

                        // В данном элементе будет находиться одна кнопка
                        Button {
                            anchors.fill: parent
                            anchors.margins: 0
                             Rectangle {
                                 color: Color
                                 anchors.fill: parent
                                 border.width: 0

                                 Text{
                                     color: FontColor
                                     font.family: "Arial"
                                     font.pointSize: 12
                                     x: 10
                                     y: 3
                                     text: name + Tool + Base
                                 }
                             }

                            onClicked: {
                                index_ext_priv = index_ext
                                index_ext = index
                                listModel.set(index_ext, {Color: "white"})
                                listModel.set(index_ext, {FontColor: "#4c4e50"})
                                listModel.set(index_ext_priv, {Color: "#2e2f30"})
                                listModel.set(index_ext_priv, {FontColor: "white"})
                            }

                            Keys.onReleased: {
                               // if(event.key === Qt.Key_)
                            }

                            onDoubleClicked: {
                                index_ext_priv = index_ext
                                index_ext = index
                                newornot=false
                                dialogNPoint.openDialog()
                            }
                        }
                    }

                    // модель, в которой будут содержаться все элементы
                    model: ListModel {
                        id: listModel // задаём ей id для обращения
                    }
                }

            }

            Rectangle {
                id: rectangle_2
                x: 10
                y: 410
                width: 659
                height: 84
                color: "#2e2f30"
                border.color: "black"

                TextArea {
                    id: messages
                    font.family: "Arial"
                    font.pointSize: 12
                    readOnly: true
                    anchors.bottomMargin: -1
                    anchors.leftMargin: 0
                    anchors.topMargin: 1
                    anchors.rightMargin: 0
                    anchors.fill: parent
                }
            }

            Rectangle {
                id: infoText
                x: 10
                y: 358
                width: 659
                height: 20
                color: "#2e2f30"
                border.color: "black"


                Label {
                    id: nameProg
                    font.family: "Arial"
                    font.pointSize: 10
                    anchors.fill: parent
                    color: "#ffffff"
                    text: qsTr("Имя выбранной программы: " + file)
                    anchors.rightMargin: -4
                    anchors.bottomMargin: -1
                    anchors.leftMargin: 4
                    anchors.topMargin: 3
                }
            }

            Label {
                id: label
                x: 10
                y: 390
                font.family: "Arial"
                font.pointSize: 11
                color: "#ffffff"
                text: qsTr("Аварийные и информационные сообщения:")
            }

            Label {
                id: label1
                x: 10
                y: 11
                width: 271
                height: 17
                font.family: "Arial"
                font.pointSize: 11
                color: "#ffffff"
                text: qsTr("Листинг программы робота:")
            }

            Button {
                id: butJoinMove
                x: 17
                y: 508
                width: 90
                height: 48
                flat: true
                autoRepeat: false

                contentItem:
                    Text {
                    text: qsTr("Joint")
                    font: butJoinMove.font
                    opacity: enabled ? 1.0 : 0.3
                    color: butJoinMove.down ? "#4c4e50" : "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }

                background: Rectangle {
                    anchors.fill: parent
                    border.color: "#008000"
                    color: butJoinMove.down ? "white" : "#4c4e50"
                    radius: 5
                }

                onClicked: {
                    newornot=true
                    dialogNPoint.openDialog()
                }
            }

            Button {
                id: butLinMove
                x: 118
                y: 508
                width: 90
                height: 48
                flat: true
                autoRepeat: false

                contentItem: Text {
                    text: qsTr("Lin")
                    font: butLinMove.font
                    opacity: enabled ? 1.0 : 0.3
                    color: butLinMove.down ? "#4c4e50" : "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }

                background: Rectangle {
                    anchors.fill: parent
                    border.color: "#008000"
                    color: butLinMove.down ? "white" : "#4c4e50"
                    radius: 5
                }

                onClicked: {

                }
            }

            Dialog {
                id: dialogDelLine
                x: 250
                y: 250
                width: 350
                height: 150
                title: "Удалить линию"
                modal: false
                standardButtons: Dialog.Ok | Dialog.Cancel

                onAccepted: {
                    var splitText = listModel.get(index_ext).name.split(" ")
                    appCore.deleteLineFromFile(file, path, splitText[2])
                    listModel.remove(index_ext)

                   // listModel.set(index_ext, {name: " PTP " + textNamePoint.text+" ",
                               //   Tool: " Tool: "+ textNumTool.text, Base: " Base: "+ textNumBase.text})
                }
            }

            Button {
                id: butDelLine
                x: 219
                y: 508
                width: 136
                height: 48
                contentItem: Text {
                    color: butDelLine.down ? "#4c4e50" : "white"
                    text: qsTr("Удалить линию")
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font: butDelLine.font
                    elide: Text.ElideRight
                    opacity: enabled ? 1.0 : 0.3
                }
                background: Rectangle {
                    color: butDelLine.down ? "white" : "#4c4e50"
                    radius: 5
                    anchors.fill: parent
                    border.color: "#008000"
                }
                autoRepeat: false
                flat: true

                onClicked: {

                    dialogDelLine.open()
                }
            }

            Button {
                id: butTouchUp

                x: 642
                y: 508
                width: 148
                height: 48
                //text: qsTr("Сохранить позицию")
                flat: true
                autoRepeat: false

                contentItem: Text {
                    text: qsTr("Сохранить позицию")
                    font: butTouchUp.font
                    opacity: enabled ? 1.0 : 0.3
                    color: butTouchUp.down ? "#4c4e50" : "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }

                background: Rectangle {
                    anchors.fill: parent
                    border.color: "#008000"
                    color: butTouchUp.down ? "white" : "#4c4e50"
                    radius: 5
                }

                onClicked: {
                   //newornot=true
                   //dialogNPoint.openDialog()
                }
            }

        }
        // третья вкладка SwipeView
        Item {
            id: thirdPage

            function updateDate(state){
                lab_pos.text = "";
                let arr_str;
                let arr_name;
                if(state==="coords"){
                    arr_name = ["x", "y", "z", "w", "p", "r"];
                    arr_str = appCore.getActCoord();
                }
                if(state==="axis"){
                    arr_name = ["A1", "A2", "A3", "A4", "A5", "A6"];
                    arr_str = appCore.getActAngles();
                }
                 for (var i in arr_str){
                    lab_pos.text += arr_name[i] + " " + parseFloat(arr_str[i]).toFixed(2) + ";";
                 }
            }


            Label {
                id: label2
                x: 19
                y: 60
                width: 131
                height: 19
                text: "Актуальня позиция:"
                color: "white"
            }

            Label {
                id: lab_pos
                x: 154
                y: 61
                width: 12
                height: 13
                color: "white"
            }

            Button {
                id: butAxisMastering

                x: 11
                y: 504
                width: 187
                height: 48
                flat: true
                autoRepeat: false

                contentItem: Text {
                    text: qsTr("Выполнить мастеризацию")
                    font: butTouchUp.font
                    opacity: enabled ? 1.0 : 0.3
                    color: butTouchUp.down ? "#4c4e50" : "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }

                background: Rectangle {
                    anchors.fill: parent
                    border.color: "#008000"
                    color: butTouchUp.down ? "white" : "#4c4e50"
                    radius: 5
                }

                onClicked: {
                    appCore.setAxisMastering(true)
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

        onCurrentIndexChanged: {
            if(swipeView.currentIndex==1)
               manualMoveModul.labSpeedText((15-appCore.getAxisSpeed()/100000)*10) //lab_speed.text = (15-appCore.getAxisSpeed()/100000)*10

            if(swipeView.currentIndex==2){
                //если выбрано перемещение по осям
                if(manualMoveModul.currentIndexCB1()===0){
                    thirdPage.updateDate("axis")
                }
                if(manualMoveModul.currentIndexCB1()===1){
                    thirdPage.updateDate("coords")
                }
            }
        }
    }

}
