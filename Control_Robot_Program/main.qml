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

    SwipeView {
        id: swipeView
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent

        currentIndex: 1

        Connections {
            target: appCore // Указываем целевое соединение
//            onSendToQml: {
//                textArea.text = count
//            }
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
                    folder: "file:///D:\\TEST_fILE\\"  //"file:///home/yastrebov/QT_Project/Control_Robot/Control_Robot_Program/Dir/Program/"
                    nameFilters: ["*.*"]

                    onCountChanged: {
                       path = "D:\\TEST_fILE"
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
                        appCore.createFile(path + "\\"+ textField.text + ".src", "Hello TEXT")
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
                    appCore.deleteFile(path + "\\"+ file);
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
                    var readFromFile = appCore.readFromFile(path + "\\"+ file)
                    var splitText = readFromFile.split('\n');
                    var textToFor = "";

                    for(var i = 0; i < splitText.length; i++){
                       textToFor +=  splitText[i]
                       if(splitText[i]==="</font> "){
                           textRobotProgram.append(textToFor + "</font>")
                           textToFor = ""
                        }
                    }

                    actTextProg = ""
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

            Rectangle {
                id: rectangle
                x: 10
                y: 34
                width: 659
                height: 324
                color: "#2e2f30"
                border.color: "black"

                TextEdit {
                    id: textRobotProgram
                    textFormat: TextEdit.AutoText
                    selectByMouse: true
                    font.family: "Arial"
                    font.pointSize: 14
                    //readOnly: true
                    cursorVisible: true
                    anchors.rightMargin: 0
                    anchors.leftMargin: 0
                    anchors.topMargin: 2
                    anchors.bottomMargin: -1
                    anchors.fill: parent
                    //color: "#008000"  //"#d6853b"
                    onCursorPositionChanged: {
                        label2.text = lineCount
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

            Rectangle {
                id: manualMoves
                x: 675
                y: 34
                width: 115
                height: 460
                color: "#2e2f30"
                border.color: "black"
                border.width: 1

               Button {
                        id: but_A1_Plus
                        x: 2
                        y: 100
                        width: parent.width/2-3
                        height: 48
                        flat: true
                        autoRepeat: false

                        contentItem: Text {
                            id: textA1P
                            text: qsTr("A1+")
                            font: but_A1_Plus.font
                            opacity: enabled ? 1.0 : 0.3
                            color: but_A1_Plus.down ? "#4c4e50" : "white"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            elide: Text.ElideRight
                        }

                        background: Rectangle {
                            anchors.fill: parent
                            border.color: "#008000"
                            color: but_A1_Plus.down ? "white" : "#4c4e50"
                            radius: 5
                        }
                        onPressed: {
                            var tempFloor = Number.parseFloat(comboBox.currentText);
                            //если выбрано перемещение по осям
                            if(comboBox1.currentIndex==0){
                                appCore.jointManMove(1, tempFloor)
                            }
                            if(comboBox1.currentIndex==1){
                                appCore.cartesianManMove(1, tempFloor)
                            }
                        }
                        onReleased: {
                            appCore.stopMove()
                        }
                }

                Button {
                    id: but_A1_Minus
                    x: but_A1_Plus.width+3
                    y: but_A1_Plus.y
                    width: parent.width/2-3
                    height: 48
                    flat: true
                    autoRepeat: false

                    contentItem: Text {
                        id: textA1M
                        text: qsTr("A1-")
                        font: but_A1_Minus.font
                        opacity: enabled ? 1.0 : 0.3
                        color: but_A1_Minus.down ? "#4c4e50" : "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideRight
                    }

                    background: Rectangle {
                        anchors.fill: parent
                        border.color: "#008000"
                        color: but_A1_Minus.down ? "white" : "#4c4e50"
                        radius: 5
                    }
                    onPressed: {
                        var tempFloor = -(Number.parseFloat(comboBox.currentText));
                        //если выбрано перемещение по осям
                        if(comboBox1.currentIndex==0){
                            appCore.jointManMove(1, tempFloor)
                        }
                        if(comboBox1.currentIndex==1){
                            appCore.cartesianManMove(1, tempFloor)
                        }
                    }
                    onReleased: {
                        appCore.stopMove()
                    }
                }

                Button {
                    id: but_A2_Plus
                    x: 2
                    y: but_A1_Plus.height + but_A1_Plus.y
                    width: parent.width/2-3
                    height: 48
                    focusPolicy: Qt.WheelFocus
                    flat: true
                    autoRepeat: false

                    contentItem: Text {
                        id: textA2P
                        text: qsTr("A2+")
                        font: but_A2_Plus.font
                        opacity: enabled ? 1.0 : 0.3
                        color: but_A2_Plus.down ? "#4c4e50" : "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideRight
                    }

                    background: Rectangle {
                        anchors.fill: parent
                        border.color: "#008000"
                        color: but_A2_Plus.down ? "white" : "#4c4e50"
                        radius: 5
                    }

                    onPressed: {
                        var tempFloor = Number.parseFloat(comboBox.currentText);
                        //если выбрано перемещение по осям
                        if(comboBox1.currentIndex==0){
                            appCore.jointManMove(2, tempFloor)
                        }
                        if(comboBox1.currentIndex==1){
                            appCore.cartesianManMove(2, tempFloor)
                        }
                    }
                    onReleased: {
                        appCore.stopMove()
                    }
                }
                Button {
                    id: but_A2_Minus
                    x: but_A2_Plus.width+3
                    y: but_A1_Plus.height + but_A1_Plus.y
                    width: parent.width/2-3
                    height: 48
                    flat: true
                    autoRepeat: false

                    contentItem: Text {
                        id: textA2M
                        text: qsTr("A2-")
                        font: but_A2_Minus.font
                        opacity: enabled ? 1.0 : 0.3
                        color: but_A2_Minus.down ? "#4c4e50" : "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideRight
                    }

                    background: Rectangle {
                        anchors.fill: parent
                        border.color: "#008000"
                        color: but_A2_Minus.down ? "white" : "#4c4e50"
                        radius: 5
                    }

                    onPressed: {
                        var tempFloor = -(Number.parseFloat(comboBox.currentText));
                        //если выбрано перемещение по осям
                        if(comboBox1.currentIndex==0){
                            appCore.jointManMove(2, tempFloor)
                        }
                        if(comboBox1.currentIndex==1){
                            appCore.cartesianManMove(2, tempFloor)
                        }
                    }
                    onReleased: {
                        appCore.stopMove()
                    }
                }

                Button {
                    id: but_A3_Plus
                    x: 2
                    y: but_A1_Plus.height*2 + but_A1_Plus.y
                    width: parent.width/2-3
                    height: 48
                    flat: true
                    autoRepeat: false

                    contentItem: Text {
                        id: textA3P
                        text: qsTr("A3+")
                        font: but_A3_Plus.font
                        opacity: enabled ? 1.0 : 0.3
                        color: but_A3_Plus.down ? "#4c4e50" : "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideRight
                    }

                    background: Rectangle {
                        anchors.fill: parent
                        border.color: "#008000"
                        color: but_A3_Plus.down ? "white" : "#4c4e50"
                        radius: 5
                    }

                    onPressed: {
                        var tempFloor = Number.parseFloat(comboBox.currentText);
                        //если выбрано перемещение по осям
                        if(comboBox1.currentIndex==0){
                            appCore.jointManMove(3, tempFloor)
                        }
                        if(comboBox1.currentIndex==1){
                            appCore.cartesianManMove(3, tempFloor)
                        }
                    }
                    onReleased: {
                        appCore.stopMove()
                    }
                }
                Button {
                    id: but_A3_Minus
                    x: but_A3_Plus.width+3
                    y: but_A1_Plus.height*2 + but_A1_Plus.y
                    width: parent.width/2-3
                    height: 48
                    flat: true
                    autoRepeat: false

                    contentItem: Text {
                        id: textA3M
                        text: qsTr("A3-")
                        font: but_A3_Minus.font
                        opacity: enabled ? 1.0 : 0.3
                        color: but_A3_Minus.down ? "#4c4e50" : "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideRight
                    }

                    background: Rectangle {
                        anchors.fill: parent
                        border.color: "#008000"
                        color: but_A3_Minus.down ? "white" : "#4c4e50"
                        radius: 5
                    }

                    onPressed: {
                        var tempFloor = -(Number.parseFloat(comboBox.currentText));
                        //если выбрано перемещение по осям
                        if(comboBox1.currentIndex==0){
                            appCore.jointManMove(3, tempFloor)
                        }
                        if(comboBox1.currentIndex==1){
                            appCore.cartesianManMove(3, tempFloor)
                        }
                    }
                    onReleased: {
                        appCore.stopMove()
                    }
                }

                Button {
                    id: but_A4_Plus
                    x: 2
                    y: but_A1_Plus.height*3 + but_A1_Plus.y
                    width: parent.width/2-3
                    height: 48
                    flat: true
                    autoRepeat: false

                    contentItem: Text {
                        id: textA4P
                        text: qsTr("A4+")
                        font: but_A4_Plus.font
                        opacity: enabled ? 1.0 : 0.3
                        color: but_A4_Plus.down ? "#4c4e50" : "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideRight
                    }

                    background: Rectangle {
                        anchors.fill: parent
                        border.color: "#008000"
                        color: but_A4_Plus.down ? "white" : "#4c4e50"
                        radius: 5
                    }

                    onPressed: {
                        var tempFloor = Number.parseFloat(comboBox.currentText);
                        //если выбрано перемещение по осям
                        if(comboBox1.currentIndex==0){
                            appCore.jointManMove(4, tempFloor)
                        }
                        if(comboBox1.currentIndex==1){
                            appCore.cartesianManMove(4, tempFloor)
                        }
                    }
                    onReleased: {
                        appCore.stopMove()
                    }
                }
                Button {
                    id: but_A4_Minus
                    x: but_A4_Plus.width+3
                    y: but_A1_Plus.height*3 + but_A1_Plus.y
                    width: parent.width/2-3
                    height: 48
                    flat: true
                    autoRepeat: false

                    contentItem: Text {
                        id: textA4M
                        text: qsTr("A4-")
                        font: but_A4_Minus.font
                        opacity: enabled ? 1.0 : 0.3
                        color: but_A4_Minus.down ? "#4c4e50" : "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideRight
                    }

                    background: Rectangle {
                        anchors.fill: parent
                        border.color: "#008000"
                        color: but_A4_Minus.down ? "white" : "#4c4e50"
                        radius: 5
                    }

                    onPressed: {
                        var tempFloor = -(Number.parseFloat(comboBox.currentText));
                        //если выбрано перемещение по осям
                        if(comboBox1.currentIndex==0){
                            appCore.jointManMove(1, tempFloor)
                        }
                        if(comboBox1.currentIndex==4){
                            appCore.cartesianManMove(4, tempFloor)
                        }
                    }
                    onReleased: {
                        appCore.stopMove()
                    }
                }

                Button {
                    id: but_A5_Plus
                    x: 2
                    y: but_A1_Plus.height*4 + but_A1_Plus.y
                    width: parent.width/2-3
                    height: 48
                    flat: true
                    autoRepeat: false

                    contentItem: Text {
                        id: textA5P
                        text: qsTr("A5+")
                        font: but_A5_Plus.font
                        opacity: enabled ? 1.0 : 0.3
                        color: but_A5_Plus.down ? "#4c4e50" : "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideRight
                    }

                    background: Rectangle {
                        anchors.fill: parent
                        border.color: "#008000"
                        color: but_A5_Plus.down ? "white" : "#4c4e50"
                        radius: 5
                    }
                    onPressed: {
                        var tempFloor = Number.parseFloat(comboBox.currentText);
                        //если выбрано перемещение по осям
                        if(comboBox1.currentIndex==0){
                            appCore.jointManMove(5, tempFloor)
                        }
                        if(comboBox1.currentIndex==1){
                            appCore.cartesianManMove(5, tempFloor)
                        }
                    }
                    onReleased: {
                        appCore.stopMove()
                    }
                }
                Button {
                    id: but_A5_Minus
                    x: but_A5_Plus.width+3
                    y: but_A1_Plus.height*4 + but_A1_Plus.y
                    width: parent.width/2-3
                    height: 48
                    flat: true
                    autoRepeat: false

                    contentItem: Text {
                        id: textA5M
                        text: qsTr("A5-")
                        font: but_A5_Minus.font
                        opacity: enabled ? 1.0 : 0.3
                        color: but_A5_Minus.down ? "#4c4e50" : "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideRight
                    }

                    background: Rectangle {
                        anchors.fill: parent
                        border.color: "#008000"
                        color: but_A5_Minus.down ? "white" : "#4c4e50"
                        radius: 5
                    }
                    onPressed: {
                        var tempFloor = -(Number.parseFloat(comboBox.currentText));
                        //если выбрано перемещение по осям
                        if(comboBox1.currentIndex==0){
                            appCore.jointManMove(5, tempFloor)
                        }
                        if(comboBox1.currentIndex==1){
                            appCore.cartesianManMove(5, tempFloor)
                        }
                    }
                    onReleased: {
                        appCore.stopMove()
                    }
                }

                Button {
                    id: but_A6_Plus
                    x: 2
                    y: but_A1_Plus.height*5 + but_A1_Plus.y
                    width: parent.width/2-3
                    height: 48
                    flat: true
                    autoRepeat: false

                    contentItem: Text {
                        id: textA6P
                        text: qsTr("A6+")
                        font: but_A6_Plus.font
                        opacity: enabled ? 1.0 : 0.3
                        color: but_A6_Plus.down ? "#4c4e50" : "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideRight
                    }

                    background: Rectangle {
                        anchors.fill: parent
                        border.color: "#008000"
                        color: but_A6_Plus.down ? "white" : "#4c4e50"
                        radius: 5
                    }
                    onPressed: {
                        var tempFloor = Number.parseFloat(comboBox.currentText);
                        //если выбрано перемещение по осям
                        if(comboBox1.currentIndex==0){
                            appCore.jointManMove(6, tempFloor)
                        }
                        if(comboBox1.currentIndex==1){
                            appCore.cartesianManMove(6, tempFloor)
                        }
                    }
                    onReleased: {
                        appCore.stopMove()
                    }
                }
                Button {
                    id: but_A6_Minus
                    x: but_A6_Plus.width+3
                    y: but_A1_Plus.height*5 + but_A1_Plus.y
                    width: parent.width/2-3
                    height: 48
                    flat: true
                    autoRepeat: false

                    contentItem: Text {
                        id: textA6M
                        text: qsTr("A6-")
                        font: but_A6_Minus.font
                        opacity: enabled ? 1.0 : 0.3
                        color: but_A6_Minus.down ? "#4c4e50" : "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideRight
                    }

                    background: Rectangle {
                        anchors.fill: parent
                        border.color: "#008000"
                        color: but_A6_Minus.down ? "white" : "#4c4e50"
                        radius: 5
                    }

                    onPressed: {
                        var tempFloor = -(Number.parseFloat(comboBox.currentText));
                        //если выбрано перемещение по осям
                        if(comboBox1.currentIndex==0){
                            appCore.jointManMove(6, tempFloor)
                        }
                        if(comboBox1.currentIndex==1){
                            appCore.cartesianManMove(6, tempFloor)
                        }
                    }
                    onReleased: {
                        appCore.stopMove()
                    }
                }

                ComboBox {
                    id: comboBox
                    x: 2
                    y: 8
                    width: 110
                    height: 25
                    displayText: currentText
                    flat: true

                    contentItem: Text {
                        id: textCB_Inc
                       // text: comboBox.displayText
                        text: comboBox.currentText
                        font: comboBox.font
                        opacity: enabled ? 1.0 : 0.3
                        color:  "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideRight
                    }

                    background: Rectangle {
                        anchors.fill: parent
                        border.color: "#008000"
                        color: "#4c4e50"
                        radius: 1
                    }

                    model: ListModel {
                        id: model
                        ListElement { text: "1" }
                        ListElement { text: "10" }
                        ListElement { text: "45" }
                        ListElement { text: "90" }
                        ListElement { text: "Бесконечно" }
                    }
                    onActivated: {
                        textCB_Inc.text = comboBox.currentText
                    }
                }

                ComboBox {
                    id: comboBox1
                    x: 2
                    y: 54
                    width: 110
                    height: 27
                    displayText: currentText
                    flat: true

                    contentItem: Text {
                        text: comboBox1.displayText
                        font: comboBox1.font
                        opacity: enabled ? 1.0 : 0.3
                        color:  "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideRight
                    }

                    background: Rectangle {
                        anchors.fill: parent
                        border.color: "#008000"
                        color: "#4c4e50"
                        radius: 1
                    }

                    model: ListModel {
                        id: model2
                        ListElement { text: "Оси"}
                        ListElement { text: "Мировая"}
                    }

                    onActivated: {
                        model.clear()
                        if(comboBox1.currentIndex == 0){
                              model.append({"text":"1"})
                              model.append({"text":"10"})
                              model.append({"text":"45"})
                              model.append({"text":"90"})
                              model.append({"text":"Бесконечно"})
                              textCB_Inc.text = "1"
                              textA1P.text = "A1+"
                              textA2P.text = "A2+"
                              textA3P.text = "A3+"
                              textA4P.text = "A4+"
                              textA5P.text = "A5+"
                              textA6P.text = "A6+"
                              textA1M.text = "A1-"
                              textA2M.text = "A2-"
                              textA3M.text = "A3-"
                              textA4M.text = "A4-"
                              textA5M.text = "A5-"
                              textA6M.text = "A6-"
                        }
                        if(comboBox1.currentIndex == 1){
                              model.append({"text":"0.5"})
                              model.append({"text":"1"})
                              model.append({"text":"10"})
                              model.append({"text":"100"})
                              model.append({"text":"Бесконечно"})
                              textCB_Inc.text = "0.5"
                              textA1P.text = "X+"
                              textA2P.text = "Y+"
                              textA3P.text = "Z+"
                              textA4P.text = "W+"
                              textA5P.text = "P+"
                              textA6P.text = "R+"
                              textA1M.text = "X-"
                              textA2M.text = "Y-"
                              textA3M.text = "Z-"
                              textA4M.text = "W-"
                              textA5M.text = "P-"
                              textA6M.text = "R-"
                        }
                    }

                }

//                Label {
//                    id: label2
//                    x: 17
//                    y: 416
//                    text: comboBox1.currentIndex
//                }
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

            Dialog {
                id: dialogNewPoint
                x: 150
                y: 250
                width: 550
                height: 150
                title: "Введите параметры новой точки"
                modal: false
                standardButtons: Dialog.Ok | Dialog.Cancel

                Label {
                    id: labelNamePoint
                    x: 3
                    y: 5
                    font.family: "Arial"
                    font.pointSize: 11
                    color: "black"
                    text: qsTr("Имя:")
                }

                TextField {
                    id: textNamePoint
                    x: 40
                    width: 70
                    height: 30
                    font.family: "Arial"
                    font.pointSize: 12
                }

                Label {
                    id: labelNumTool
                    x: 125
                    y: 5
                    font.family: "Arial"
                    font.pointSize: 11
                    color: "black"
                    text: qsTr("Номер инструмента:")
                }

                TextField {
                    id: textNumTool
                    x: 270
                    width: 70
                    height: 30
                    font.family: "Arial"
                    font.pointSize: 12
                }

                Label {
                    id: labelNumBase
                    x: 355
                    y: 5
                    font.family: "Arial"
                    font.pointSize: 11
                    color: "black"
                    text: qsTr("Номер базы:")
                }

                TextField {
                    id: textNumBase
                    x: 450
                    width: 70
                    height: 30
                    font.family: "Arial"
                    font.pointSize: 12
                }

                onAccepted: {
                    if (textNamePoint.text != "" && textNumTool.text != "" && textNumBase.text != ""){
                        textRobotProgram.append("<font color='red'>Joint</font> <font color='green'>" +textNamePoint.text+ "<font color='red'>Tool </font> </font>
                        <font color='green'>" +textNumTool.text+ "<font color='red'>Base </font> </font> <font color='green'>" +textNumBase.text+ "\n</font>")

                        actTextProg += textRobotProgram.text + "<font color='red'>Joint</font> <font color='green'>" +textNamePoint.text+ "<font color='red'>Tool </font> </font>
                        <font color='green'>" +textNumTool.text+ "<font color='red'>Base </font> </font> <font color='green'>" +textNumBase.text+ "\n</font>"

                        appCore.writeToFile(path + "\\"+ file, actTextProg)
                    }
                }
            }


            Button {
                id: butJoinMove
                x: 17
                y: 508
                width: 90
                height: 48
                flat: true
                autoRepeat: false

                contentItem: Text {
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
                    dialogNewPoint.open()

                    //textRobotProgram.cursorPosition = 5
                    //textRobotProgram.moveCursorSelection(9, TextEdit.SelectCharacters)

                    textRobotProgram.lineCount = 3

                   //label2.text = textRobotProgram.getText(2, 6)
                   // textRobotProgram.text = "<font color='red'>Hello</font> <font color='green'> world \n</font>"
                   //textRobotProgram.append("<font color='red'>Joint</font> <font color='green'> P1 \n</font>")
                   //textRobotProgram.append("<font color='red'>Joint</font> <font color='green'> P2 \n</font>")
                    //appCore.createFile(path + "\\"+ file, "Hello TEXT")
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
                    //appCore.createFile(path + "\\"+ file, "Hello TEXT")     //"D:\\TEST_fILE\\TEST_CREATE_FILE.txt", "Hello TEXT");
                }
            }

            Button {
                id: butTouchUp

                x: 665
                y: 508
                width: 125
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
                    //appCore.createFile(path + "\\"+ file, "Hello TEXT")     //"D:\\TEST_fILE\\TEST_CREATE_FILE.txt", "Hello TEXT");
                }
            }

            Label {
                id: label2
                x: 408
                y: 513
                width: 47
                height: 24
                text: qsTr("Label")
            }

            Label {
                id: label3
                x: 489
                y: 513
                text: qsTr("Label")
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
