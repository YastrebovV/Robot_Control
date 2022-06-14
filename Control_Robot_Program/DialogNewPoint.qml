import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.4
import Qt.labs.folderlistmodel 2.1

Item {

    function openDialog()
    {
        dialogNewPoint.open()
    }

    Dialog {
        objectName: "dialogNewPoint"
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
            if(newornot){
                listModel.append({name: " PTP " + textNamePoint.text+" ",
                                     Tool: " Tool: "+ textNumTool.text, Base: " Base: "+ textNumBase.text, Color: "#2e2f30", FontColor: "white"})
            }else{
                listModel.set(index_ext, {name: " PTP " + textNamePoint.text+" ",
                              Tool: " Tool: "+ textNumTool.text, Base: " Base: "+ textNumBase.text})
            }

            appCore.writeToFile(file, path, "PTP", textNamePoint.text, textNumTool.text, textNumBase.text)
 //           var strArr = []
 //           for(var i = 0; i < listModel.count; i++){
 //               strArr[i] = listModel.get(i).name.split(' ')[2] + "," + listModel.get(i).Tool.split(' ')[2] +","+ listModel.get(i).Base.split(' ')[2]
 //           }


        }
    }
}
