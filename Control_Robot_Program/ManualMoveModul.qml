import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.4
import Qt.labs.folderlistmodel 2.1

Item {

    function labSpeedText(text)
    {
       lab_speed.text = text
    }

    function currentIndexCB1(){
        return comboBox1.currentIndex;
    }

    Rectangle {
        objectName: "manualMoves"
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
                y: 165
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
                    if(comboBox1.currentIndex==0)
                        thirdPage.updateDate("axis")
                    if(comboBox1.currentIndex==1)
                        thirdPage.updateDate("coords")
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
                if(comboBox1.currentIndex==0)
                   thirdPage.updateDate("axis")
                if(comboBox1.currentIndex==1)
                    thirdPage.updateDate("coords")
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
                var tempFloor = 0.0;
                if(comboBox.currentText === "Бесконечно"){
                    if(comboBox1.currentIndex==0){
                        tempFloor = 600
                    }else{
                        tempFloor = 360.0
                    }
                }else{
                    tempFloor = Number.parseFloat(comboBox.currentText);
                }

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
                if(comboBox1.currentIndex==0)
                    thirdPage.updateDate("axis")
                if(comboBox1.currentIndex==1)
                    thirdPage.updateDate("coords")
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
                var tempFloor = 0.0;
                if(comboBox.currentText === "Бесконечно"){
                    if(comboBox1.currentIndex==0){
                        tempFloor = -600
                    }else{
                        tempFloor = -360.0
                    }
                }else{
                    tempFloor = -Number.parseFloat(comboBox.currentText);
                }
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
                if(comboBox1.currentIndex==0)
                    thirdPage.updateDate("axis")
                if(comboBox1.currentIndex==1)
                    thirdPage.updateDate("coords")
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
                if(comboBox1.currentIndex==0)
                    thirdPage.updateDate("axis")
                if(comboBox1.currentIndex==1)
                    thirdPage.updateDate("coords")
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
                if(comboBox1.currentIndex==0)
                    thirdPage.updateDate("axis")
                if(comboBox1.currentIndex==1)
                    thirdPage.updateDate("coords")
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
                if(comboBox1.currentIndex==0)
                    thirdPage.updateDate("axis")
                if(comboBox1.currentIndex==1)
                    thirdPage.updateDate("coords")
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
                    appCore.jointManMove(4, tempFloor)
                }
                if(comboBox1.currentIndex==4){
                    appCore.cartesianManMove(4, tempFloor)
                }
            }
            onReleased: {
                appCore.stopMove()
                if(comboBox1.currentIndex==0)
                    thirdPage.updateDate("axis")
                if(comboBox1.currentIndex==1)
                    thirdPage.updateDate("coords")
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
                if(comboBox1.currentIndex==0)
                    thirdPage.updateDate("axis")
                if(comboBox1.currentIndex==1)
                    thirdPage.updateDate("coords")
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
                if(comboBox1.currentIndex==0)
                    thirdPage.updateDate("axis")
                if(comboBox1.currentIndex==1)
                    thirdPage.updateDate("coords")
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
                if(comboBox1.currentIndex==0)
                    thirdPage.updateDate("axis")
                if(comboBox1.currentIndex==1)
                    thirdPage.updateDate("coords")
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
                if(comboBox1.currentIndex==0)
                    thirdPage.updateDate("axis")
                if(comboBox1.currentIndex==1)
                    thirdPage.updateDate("coords")
            }
        }

        ComboBox {
            id: comboBox
            x: 2
            y: 73
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
            y: 119
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

        Button {
            id: but_Speed_Plus
            x: 2
            y: 35
            width: parent.width/2-3
            height: 24
            autoRepeat: false
            background: Rectangle {
                color: but_Speed_Plus.down ? "white" : "#4c4e50"
                radius: 5
                anchors.fill: parent
                border.color: "#008000"
            }
            flat: true
            contentItem: Text {
                id: textSpPl
                color: but_Speed_Plus.down ? "#4c4e50" : "white"
                text: qsTr("+")
                elide: Text.ElideRight
                opacity: enabled ? 1.0 : 0.3
                font: but_Speed_Plus.font
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            onClicked: {
                var speed = 0;
                if(appCore.getAxisSpeed() > 400000)
                   appCore.setSpeed(appCore.getAxisSpeed()-100000)
                speed = (14-appCore.getAxisSpeed()/100000)*10
                if (speed > 0 && speed < 100){
                   lab_speed.text = speed
                }else if(speed ===0){
                   lab_speed.text = 0
                }else if(speed >=100){
                   lab_speed.text = 100
                }
            }
        }
        Button {
            id: but_Speed_Mn
            x: 58
            y: 35
            width: parent.width/2-3
            height: 24
            autoRepeat: false
            background: Rectangle {
                color: but_Speed_Mn.down ? "white" : "#4c4e50"
                radius: 5
                anchors.fill: parent
                border.color: "#008000"
            }
            flat: true
            contentItem: Text {
                id: textSpMn
                color: but_Speed_Mn.down ? "#4c4e50" : "white"
                text: qsTr("-")
                elide: Text.ElideRight
                opacity: enabled ? 1.0 : 0.3
                font: but_Speed_Mn.font
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
            onClicked: {
                var speed = 0;
                if(appCore.getAxisSpeed() < 1400000)
                   appCore.setSpeed(appCore.getAxisSpeed()+100000)
                speed = (14-appCore.getAxisSpeed()/100000)*10
                if (speed > 0 && speed < 100){
                   lab_speed.text = speed
                }else if(speed ===0){
                   lab_speed.text = 0
                }else if(speed >=100){
                   lab_speed.text = 100
                }
            }
        }

        Label {
            id: label3
            x: 2
            y: 10
            width: 131
            height: 19
            color: "#ffffff"
            text: "Скорость:"
        }

        Label {
            id: lab_speed
            x: 71
            y: 10
            width: 12
            height: 13
            color: "#ffffff"
        }
    }
}
