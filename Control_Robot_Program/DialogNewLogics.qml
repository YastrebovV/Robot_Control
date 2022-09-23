import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.4
import Qt.labs.folderlistmodel 2.1
import QtQuick.VirtualKeyboard 2.1

Item {
    id: itemDialog
    property int type: 0;
    property int tool: 0;
    property int base: 0;
    property string namePoint: "";

    property var newElements;

    function openDialog()
    {
        dialogNewLogics.open()
    }

    function selectionElements(index)
    {
        var elements = ' ';
        switch(index){
         case 0: elements = '
        import QtQuick 2.7
        import QtQuick.Controls 2.3
        import QtQuick.Layouts 1.0
        import QtQuick.Controls.Styles 1.4
        import Qt.labs.folderlistmodel 2.1
        import QtQuick.VirtualKeyboard 2.1

Rectangle{
            Label {
                id: labelTime
                x: 193
                y: 8
                font.family: "Arial"
                font.pointSize: 11
                color: "black"
                text: qsTr("Время в секундах:")
            }

             TextField {
                id: textTime
                x: 327
                y: 1
                width: 41
                height: 30
                font.family: "Arial"
                font.pointSize: 12
                inputMethodHints: Qt.ImhFormattedNumbersOnly
                text: newornot ? "" : listModel.get(index_ext).name
             }
}
'; dialogNewLogics.width = 400; dialogNewLogics.height = 172; break;
         case 1: elements = '
        import QtQuick 2.7
        import QtQuick.Controls 2.3
        import QtQuick.Layouts 1.0
        import QtQuick.Controls.Styles 1.4

Rectangle{
            Label {
                id: labelIO
                x: 431
                y: 12
                font.family: "Arial"
                font.pointSize: 11
                color: "black"
                text: qsTr("Номер вх/вых:")
             }

            TextField {
                id: textIO
                x: 538
                y: 5
                width: 41
                height: 30
                font.family: "Arial"
                font.pointSize: 12
                inputMethodHints: Qt.ImhFormattedNumbersOnly
            }

            Label {
                id: labelInOrOut
                x: 194
                y: 11
                font.family: "Arial"
                font.pointSize: 11
                color: "black"
                text: qsTr("Выбрать вх. ил вых.:")
            }

            ComboBox {
                id: inOrOut
                x: 351
                y: 5
                width: 70
                height: 30
                font.family: "Arial"
                font.pointSize: 12

                background: Rectangle{
                    border.color: "#008000"
                    color:"white"
                }

                model: ["In", "Out"]
            }
}
'; dialogNewLogics.width = 610; dialogNewLogics.height = 172; break;
         case 2: elements = '
        import QtQuick 2.7
        import QtQuick.Controls 2.3
        import QtQuick.Layouts 1.0
        import QtQuick.Controls.Styles 1.4
Rectangle{
        Label {
            id: labelOut
            x: 201
            y: 12
            font.family: "Arial"
            font.pointSize: 11
            color: "black"
            text: qsTr("Номер выхода:")
        }

        TextField {
            id: textNumOut
            x: 317
            y: 5
            width: 41
            height: 30
            font.family: "Arial"
            font.pointSize: 12
            text: qsTr("1")
            inputMethodHints: Qt.ImhFormattedNumbersOnly
        }

        Label {
            id: labelOutState
            x: 364
            y: 12
            font.family: "Arial"
            font.pointSize: 11
            color: "black"
            text: qsTr("Состояние выхода:")
        }

        ComboBox {
            id: inOrOut
            x: 510
            y: 5
            width: 96
            height: 30
            font.family: "Arial"
            font.pointSize: 12

            background: Rectangle{
                border.color: "#008000"
                color:"white"
            }

            model: ["False", "True"]
        }
}
'; dialogNewLogics.width = 645; dialogNewLogics.height = 172; break;
         case 3: elements = '
        import QtQuick 2.7
        import QtQuick.Controls 2.3
        import QtQuick.Layouts 1.0
        import QtQuick.Controls.Styles 1.4
Rectangle{
        Label {
            id: labelPulse
            x: 201
            y: 12
            font.family: "Arial"
            font.pointSize: 11
            color: "black"
            text: qsTr("Номер выхода:")
        }

        TextField {
            id: textNumPulse
            x: 317
            y: 5
            width: 41
            height: 30
            font.family: "Arial"
            font.pointSize: 12
            text: qsTr("1")
            inputMethodHints: Qt.ImhFormattedNumbersOnly
        }

        Label {
            id: labelPulseState
            x: 364
            y: 12
            font.family: "Arial"
            font.pointSize: 11
            color: "black"
            text: qsTr("Состояние выхода:")
        }

        ComboBox {
            id: inOrOut
            x: 510
            y: 5
            width: 96
            height: 30
            font.family: "Arial"
            font.pointSize: 12

            background: Rectangle{
                border.color: "#008000"
                color:"white"
            }

            model: ["False", "True"]
        }

        Label {
            id: labelPulseTime
            x: 201
            y: 53
            font.family: "Arial"
            font.pointSize: 11
            color: "black"
            text: qsTr("Время импульса:")
        }

        TextField {
            id: textPulseTime
            x: 325
            y: 47
            width: 41
            height: 30
            font.family: "Arial"
            font.pointSize: 12
            text: qsTr("1")
            inputMethodHints: Qt.ImhFormattedNumbersOnly
        }
}
'; dialogNewLogics.width = 645; dialogNewLogics.height = 200; break;
         }
        if(newElements)
           newElements.destroy();

        newElements =  Qt.createQmlObject(elements, rec);
    }

    Dialog {
        objectName: "dialogNewLogics"
        id: dialogNewLogics
        x: 161
        y: 160
        width: 658
        height: 172
        title: "Логические операции"
        modal: false
        standardButtons: Dialog.Ok | Dialog.Cancel
     Rectangle{
        id: rec

        InputPanel {
            id: inputPanel
            z: 99
            // Меняем x, y, чтобы изменить положение клавиатуры
            x: -120
            y: 500
                 // Изменяем ширину, чтобы изменить размер клавиатуры
            width: 700

            states: State {
                name: "visible"
                when: inputPanel.active
                PropertyChanges {
                    target: inputPanel
                    y: 170
                }
            }
        }

        Label {
            id: labelTypeLogics
            x: 26
            y: 12
            width: 29
            height: 23
            font.family: "Arial"
            font.pointSize: 11
            color: "black"
            text: qsTr("Тип:")
        }
        ComboBox {
            id: logicsType
            x: 61
            y: 5
            width: 119
            height: 30
            font.family: "Arial"
            font.pointSize: 12

            background: Rectangle{
                border.color: "#008000"
                color:"white"
            }

            model: ["Wait sec", "Wait for", "OUT", "PULSE"]

            onCurrentTextChanged: {
                selectionElements(currentIndex);
            }
        }
    }
     onOpened: {
         if(newornot){
            selectionElements(0);
            logicsType.currentIndex = 0;
         }else{
             if(listModel.get(index_ext).type === "Wait sec"){
                 selectionElements(0);
                 logicsType.currentIndex = 0;
             }
             if(listModel.get(index_ext).type === "Wait for"){
                 selectionElements(1);
                 logicsType.currentIndex = 1;
             }
             if(listModel.get(index_ext).type === "OUT"){
                 selectionElements(2);
                 logicsType.currentIndex = 2;
             }
             if(listModel.get(index_ext).type === "PULSE"){
                 selectionElements(3);
                 logicsType.currentIndex = 3;
             }
         }
     }

     onAccepted: {
         var temppp =  rec
         if(newornot){
             switch(logicsType.currentIndex){
             case 0: //listModel.insert(index_ext+1,{type: logicsType.currentText, name: rec.children[2].data[1].text,
                                   //        Tool: " ", Base: " ", Color: "#2e2f30", FontColor: "white"});
                     appCore.writeLineToFile(file, path, logicsType.currentText, rec.children[3].data[1].text, "", "", index_ext+1);
                     break;
             case 1:
                     appCore.writeLineToFile(file, path, logicsType.currentText, rec.children[3].data[3].displayText, rec.children[3].data[1].text, "", index_ext+1);
                     break;
             case 2:
                     appCore.writeLineToFile(file, path, logicsType.currentText, rec.children[3].data[1].text, rec.children[3].data[3].displayText, "", index_ext+1);
                     break;
             case 3:
                     appCore.writeLineToFile(file, path, logicsType.currentText, rec.children[3].data[1].text, rec.children[3].data[3].displayText,
                     rec.children[3].data[5].text, index_ext+1);
                     break;
             }

         }else{
             var oldName = listModel.get(index_ext).name;
             switch(listModel.get(index_ext).type)
             {
                case "Wait sec": appCore.changeLineInFile(file, path, logicsType.currentText, rec.children[3].data[1].text, oldName, "", "", index_ext, false);
                              break;
                case "Wait for": appCore.changeLineInFile(file, path, logicsType.currentText, rec.children[3].data[3].displayText, oldName, rec.children[3].data[1].text, "", index_ext, false);
                              break;
                case "OUT": appCore.changeLineInFile(file, path, logicsType.currentText, rec.children[3].data[1].text, oldName, rec.children[3].data[3].displayText, "", index_ext, false);
                              break;
                case "PULSE": appCore.changeLineInFile(file, path, logicsType.currentText, rec.children[3].data[1].text, oldName.split(' ')[2], rec.children[3].data[3].displayText,
                                                       rec.children[3].data[5].text, index_ext, false);
                              break;
             }
         }
     }

     onClosed: {
     if(newElements)
         newElements.destroy()
     }
    }

}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
