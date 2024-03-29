 import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.4
import Qt.labs.folderlistmodel 2.1


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
    property bool ifDelEndLine: false


    DialogNewPoint{id: dialogNPoint}
    DialogNewLogics{id: dialogNLogics}
    OneOrTwoScreen{id: oneOrTwoScreen}

    SwipeView {
        id: swipeView
        width: 800
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
                if(type === "PTP" || type === "LIN"){
                   listModel.append({type: type, name: name,
                                     Tool: " Tool: " + tool, Base: " Base: " + base, Color: "#2e2f30", FontColor: "white"})
                }else{
                    if(type !== "PULSE"){
                        listModel.append({type: type, name: name,
                                        Tool: " " +tool, Base: " " +base, Color: "#2e2f30", FontColor: "white"})
                    }else{
                        listModel.append({type: type, name: " OUT: " + name,
                                        Tool: " State: " +tool, Base: " Time: " +base, Color: "#2e2f30", FontColor: "white"})
                    }
                }
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

                        onTextChanged: {                            
                          //  if (!fileIsDir && file !== fileName) {
                           //    file = fileName
                          //  }
                        }
                   }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                             listView.currentIndex = index
                             //if (!fileIsDir) {
                               // file = fileName
                            // }
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
                height: 160
                title: "Введите имя файла"
                modal: false
                standardButtons: Dialog.Ok | Dialog.Cancel

                TextField {
                    id: textField
                    x: 5
                    y: 20
                    width: 320
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
                    if (!dataModel.isFolder(listView.currentIndex)) {
                       file = dataModel.get(listView.currentIndex, "fileName")
                    }
                    appCore.openFile(file, path)
                    swipeView.currentIndex = 1
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

       RowLayout {
            id: rowLayout
            x: 10
            y: 34
            width: 659
            height: 324

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
                                     text: type+ " " + name +  Tool + Base//type+ " " + name + " Tool: " + Tool +" Base: " + Base
                                 }
                             }

                            onClicked: {
                                index_ext_priv = index_ext
                                index_ext = index
                                listModel.set(index_ext, {Color: "white"})
                                listModel.set(index_ext, {FontColor: "#4c4e50"})
                                if(!ifDelEndLine && index_ext_priv != index_ext){
                                    listModel.set(index_ext_priv, {Color: "#2e2f30"})
                                    listModel.set(index_ext_priv, {FontColor: "white"})
                                }
                                ifDelEndLine = false
                            }

                            Keys.onReleased: {
                               // if(event.key === Qt.Key_)
                            }

                            onDoubleClicked: {
                                index_ext_priv = index_ext
                                index_ext = index
                                newornot=false
                                if(listModel.get(index_ext).type === "PTP" || listModel.get(index_ext).type === "LIN"){
                                    dialogNPoint.openDialog()
                                }else{
                                    dialogNLogics.openDialog()
                                }
                            }
                        }
                    }

                    // модель, в которой будут содержаться все элементы
                    model: ListModel {
                        id: listModel // задаём ей id для обращения
                    }
                }
            }

        }//RowLayout

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
                id: butMovePoint
                x: 17
                y: 508
                width: 120
                height: 48
                flat: true
                autoRepeat: false

                contentItem:
                    Text {
                    text: qsTr("Добавить точку")
                    font: butMovePoint.font
                    opacity: enabled ? 1.0 : 0.3
                    color: butMovePoint.down ? "#4c4e50" : "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }

                background: Rectangle {
                    anchors.fill: parent
                    border.color: "#008000"
                    color: butMovePoint.down ? "white" : "#4c4e50"
                    radius: 5
                }

                onClicked: {
                    newornot=true
                    dialogNPoint.openDialog()
                }
            }
            Button {
                id: butLogicLine
                x: 144
                y: 508
                width: 125
                height: 48
                flat: true
                autoRepeat: false

                contentItem:
                    Text {
                    text: qsTr("Добавить логику")
                    font: butLogicLine.font
                    opacity: enabled ? 1.0 : 0.3
                    color: butLogicLine.down ? "#4c4e50" : "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }

                background: Rectangle {
                    anchors.fill: parent
                    border.color: "#008000"
                    color: butLogicLine.down ? "white" : "#4c4e50"
                    radius: 5
                }

                onClicked: {
                    newornot=true
                    dialogNLogics.openDialog()
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
                    var nameForDel = listModel.get(index_ext).name
                    if(listModel.get(index_ext).type === "PULSE")
                        nameForDel = nameForDel.split(' ')[2]
                    appCore.deleteLineFromFile(file, path, nameForDel, index_ext)
                   // listModel.remove(index_ext)
                    ifDelEndLine = true
                }
            }

            Button {
                id: butDelLine
                x: 277
                y: 508
                width: 125
                height: 48

                contentItem: Text {
                    color: butDelLine.down ? "#4c4e50" : "white"
                    text: qsTr("Удалить строку")
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

                x: 413
                y: 508
                width: 148
                height: 48
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
                    if(listModel.get(index_ext).type === "PTP" || listModel.get(index_ext).type === "LIN")
                            appCore.changeLineInFile(file, path,  listModel.get(index_ext).type, listModel.get(index_ext).name,
                                             listModel.get(index_ext).name, (listModel.get(index_ext).Tool).split(' ')[2],
                                             (listModel.get(index_ext).Base).split(' ')[2],
                                             index_ext, true)
                }
            }

            Button {
                id: startButton
                x: 657
                y: 504
                width: 60
                height: 60
                text: "Старт"

                background: Rectangle {
                    anchors.fill: parent
                    border.color: "#4c4e50"
                    color: startButton.down ? "white" : "#008000"
                    radius: 5
                }
                onClicked: {
                    appCore.startProgram()
                }
            }

            Button {
                id: stopButton
                x: 729
                y: 504
                width: 60
                height: 60
                text: "Стоп"

                background: Rectangle {
                    anchors.fill: parent
                    border.color: "#4c4e50"
                    color:  stopButton.down ? "white" : "red"
                    radius: 5
                }

                onClicked: {
                    appCore.stopProgram()
                }
            }
        }
        // третья вкладка SwipeView
        Item {
            id: thirdPage

            function updateDate(state){
                var text = '';
                var arr_str;
                var arr_name;

                if(state==="coords"){
                    arr_name = ['x', 'y', 'z', 'w', 'p', 'r'];
                    arr_str = appCore.getActCoord();
                }
                if(state==="axis"){
                    arr_name = ['A1', 'A2', 'A3', 'A4', 'A5', 'A6'];
                    arr_str = appCore.getActAngles();
                }
                 for (var i in arr_str){
                    text += arr_name[i] + " " + parseFloat(arr_str[i]).toFixed(2) + "; ";
                 }

                 return text;
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
                    lab_pos.text = '';
                    lab_pos.text = thirdPage.updateDate("axis")
                }
                if(manualMoveModul.currentIndexCB1()===1){
                    lab_pos.text = '';
                    lab_pos.text = thirdPage.updateDate("coords")
                }
            }
        }
    }

    Switch {
        id: twoScreensSwitch
        x: 658
        y: -2
        width: 75
        height: 40
        checked: false
        checkable: true

        Text{
            x: 70
            y: 12
            text: "Два экран"
            color: "white"
        }

        onCheckedChanged: {
             twoScreensSwitch.checked ? oneOrTwoScreen.numberOfScreens(2) : oneOrTwoScreen.numberOfScreens(1)

            if(manualMoveModul.data[0].children[13].currentIndex===0)
                if(twoScreensSwitch.checked)
                    rowLayout.data[1].children[0].data[1].text = thirdPage.updateDate("axis")
            if(manualMoveModul.data[0].children[13].currentIndex===1)
                if(twoScreensSwitch.checked)
                    rowLayout.data[1].children[0].data[1].text = thirdPage.updateDate("coords")
        }
    }
}
