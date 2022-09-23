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

    function openDialog()
    {

//       var dialogNP =  Qt.createQmlObject('
//        import QtQuick 2.7
//        import QtQuick.Controls 2.3
//        import QtQuick.Layouts 1.0
//        import QtQuick.Controls.Styles 1.4
//        import Qt.labs.folderlistmodel 2.1

//        Dialog {
//        objectName: "dialogNewPoint"
//        id: dialogNewPoint
//        x: 150
//        y: 250
//        width: 498
//        height: 198
//        title: "Введите параметры новой точки"
//        modal: false
//        standardButtons: Dialog.Ok | Dialog.Cancel

//        Label {
//            id: labelTypePoint
//            x: 54
//            y: 8
//            width: 29
//            height: 23
//            font.family: "Arial"
//            font.pointSize: 11
//            color: "black"
//            text: qsTr("Тип:")
//        }
//        ComboBox {
//            id: pointType
//            x: 89
//            y: 1
//            width: 85
//            height: 30
//            font.family: "Arial"
//            font.pointSize: 12

//            background: Rectangle{
//                border.color: "#008000"
//                color:"white"
//            }

//            currentIndex: type
//            displayText: currentText
//            model: ["PTP", "LIN"]

//        }
//        Label {
//            id: labelNamePoint
//            x: 193
//            y: 8
//            font.family: "Arial"
//            font.pointSize: 11
//            color: "black"
//            text: qsTr("Имя:")
//        }

//        TextField {
//            id: textNamePoint
//            x: 232
//            y: 1
//            width: 106
//            height: 30
//            font.family: "Arial"
//            font.pointSize: 12

//            text: qsTr(namePoint)
//        }

//        Label {
//            id: labelNumTool
//            x: 10
//            y: 51
//            font.family: "Arial"
//            font.pointSize: 11
//            color: "black"
//            text: qsTr("Номер инструмента:")
//        }

//        ComboBox {
//            id: numTool
//            x: 167
//            y: 45
//            width: 70
//            height: 30
//            font.family: "Arial"
//            font.pointSize: 12

//            background: Rectangle{
//                border.color: "#008000"
//                color:"white"
//            }
//            currentIndex: tool
//            displayText: currentText
//            model: ["0", "1", "2", "3", "4", "5"]
//        }

//        Label {
//            id: labelNumBase
//            x: 250
//            y: 52
//            font.family: "Arial"
//            font.pointSize: 11
//            color: "black"
//            text: qsTr("Номер базы:")
//        }
//        ComboBox {
//            id: numBase
//            x: 344
//            y: 45
//            width: 85
//            height: 30
//            font.family: "Arial"
//            font.pointSize: 12

//            background: Rectangle{
//                border.color: "#008000"
//                color:"white"
//            }

//            currentIndex: base
//            displayText: currentText
//            model: ["0", "1", "2", "3", "4", "5"]
//        }

//        onAccepted: {
//          if(textNamePoint.text !== "" && textNamePoint.text !== " "){
//            if(newornot){
//                listModel.insert(index_ext+1,{type: pointType.currentText, name: textNamePoint.text,
//                                     Tool: " Tool: " + numTool.currentText, Base: " Base: " + numBase.currentText, Color: "#2e2f30", FontColor: "white"})
//                appCore.writeLineToFile(file, path, pointType.currentText, textNamePoint.text, numTool.currentText, numBase.currentText, index_ext+1)
//            }else{
//                var oldName = listModel.get(index_ext).name;
//                listModel.set(index_ext, {type: pointType.currentText, name: textNamePoint.text,
//                              Tool: " Tool: " + numTool.currentText, Base: " Base: " +numBase.currentText})
//                appCore.changeLineInFile(file, path, pointType.currentText, textNamePoint.text, oldName, numTool.currentText, numBase.currentText, index_ext, false)
//            }
//          }
//        }
//    }', itemDialog)

        if(!newornot){
            if(listModel.get(index_ext).type === "PTP"){
                type = 0;
            }else{
                type = 1;
            }

            namePoint = listModel.get(index_ext).name
            tool = Number(listModel.get(index_ext).Tool.split(' ')[2]);
            base = Number(listModel.get(index_ext).Base.split(' ')[2]);
        }else{
            type = 0;
            tool = 0;
            base = 0;
            namePoint = "";
        }

       // dialogNP.open()

       dialogNewPoint.open()
    }

    Dialog {
        objectName: "dialogNewPoint"
        id: dialogNewPoint
        x: 148
        y: 117
        width: 498
        height: 198
        title: "Введите параметры новой точки"
        modal: false
        standardButtons: Dialog.Ok | Dialog.Cancel

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
            id: labelTypePoint
            x: 54
            y: 8
            width: 29
            height: 23
            font.family: "Arial"
            font.pointSize: 11
            color: "black"
            text: qsTr("Тип:")
        }
        ComboBox {
            id: pointType
            x: 89
            y: 1
            width: 85
            height: 30
            font.family: "Arial"
            font.pointSize: 12

            background: Rectangle{
                border.color: "#008000"
                color:"white"
            }

            currentIndex: type
            displayText: currentText
            model: ["PTP", "LIN"]

        }
        Label {
            id: labelNamePoint
            x: 193
            y: 8
            font.family: "Arial"
            font.pointSize: 11
            color: "black"
            text: qsTr("Имя:")
        }

        TextField {
            id: textNamePoint
            x: 232
            y: 1
            width: 106
            height: 30
            font.family: "Arial"
            font.pointSize: 12

            text: qsTr(namePoint)
        }

        Label {
            id: labelNumTool
            x: 10
            y: 51
            font.family: "Arial"
            font.pointSize: 11
            color: "black"
            text: qsTr("Номер инструмента:")
        }

        ComboBox {
            id: numTool
            x: 167
            y: 45
            width: 70
            height: 30
            font.family: "Arial"
            font.pointSize: 12

            background: Rectangle{
                border.color: "#008000"
                color:"white"
            }
            currentIndex: tool
            displayText: currentText
            model: ["1", "2", "3", "4", "5"]
        }

        Label {
            id: labelNumBase
            x: 250
            y: 52
            font.family: "Arial"
            font.pointSize: 11
            color: "black"
            text: qsTr("Номер базы:")
        }
        ComboBox {
            id: numBase
            x: 344
            y: 45
            width: 85
            height: 30
            font.family: "Arial"
            font.pointSize: 12

            background: Rectangle{
                border.color: "#008000"
                color:"white"
            }

            currentIndex: base
            displayText: currentText
            model: ["1", "2", "3", "4", "5"]
        }

        onAccepted: {
                  if(textNamePoint.text !== "" && textNamePoint.text !== " "){
                      if(newornot){
                         listModel.insert(index_ext+1,{type: pointType.currentText, name: textNamePoint.text,
                                             Tool: " Tool: " + numTool.currentText, Base: " Base: " + numBase.currentText, Color: "#2e2f30", FontColor: "white"})
                         appCore.writeLineToFile(file, path, pointType.currentText, textNamePoint.text, numTool.currentText, numBase.currentText, index_ext+1)
                      }else{
                        var oldName = listModel.get(index_ext).name;
                        listModel.set(index_ext, {type: pointType.currentText, name: textNamePoint.text,
                                      Tool: " Tool: " + numTool.currentText, Base: " Base: " +numBase.currentText})
                        appCore.changeLineInFile(file, path, pointType.currentText, textNamePoint.text, oldName, numTool.currentText, numBase.currentText, index_ext, false)
                      }
                  }
        }
    }
}
