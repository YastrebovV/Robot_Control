import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Window 2.2
import Qt.labs.folderlistmodel 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

        ListView {
            anchors.fill: parent
            //clip: true

            model: FolderListModel {
                id: folderListModel
                showDirsFirst: true
                folder: "file:///home/yastrebov/QT_Project/Control_Robot/Control_Robot_Program/Dir/Program/"
            }

            Button {
               id: butBack
               x: 0
               y: 0
               width: 200
               height: 50
               text: "..."

               background: Rectangle {}
            }

            delegate: Button {
                y: 100
                width: 200
                height: 50
                text: fileName

                Image {
                    y: 100
                    width: 40
                    height: 40
                    fillMode: Image.PreserveAspectFit
                    source:  fileIsDir ? "icons/folder.png" : "icons/file.png"
                }

                onClicked: {
                    if (fileIsDir) {
                        folderListModel.folder = fileURL
                    }
                }

                background: Rectangle {
                    y: 100
                   // color: "white" //fileIsDir ? "orange" : "gray"
                   // border.color: "black"
                }
            }
        }

    Button {
        y: 300
        text: "back"
        onClicked: folderListModel.folder = folderListModel.parentFolder
    }
}
