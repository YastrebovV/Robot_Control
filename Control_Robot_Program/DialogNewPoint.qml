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
                listModel.insert(index_ext+1,{type: "PTP", name: textNamePoint.text,
                                     Tool: textNumTool.text, Base: textNumBase.text, Color: "#2e2f30", FontColor: "white"})
                appCore.writeLineToFile(file, path, "PTP", textNamePoint.text, textNumTool.text, textNumBase.text, index_ext+1)
            }else{
                var oldName = listModel.get(index_ext).name;
                listModel.set(index_ext, {type: "PTP", name: textNamePoint.text,
                              Tool: textNumTool.text, Base: textNumBase.text})
                appCore.changeLineInFile(file, path, "PTP", textNamePoint.text, oldName, textNumTool.text, textNumBase.text)
            }
        }
    }
}
