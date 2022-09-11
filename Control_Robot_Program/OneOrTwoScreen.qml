import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.4
import Qt.labs.folderlistmodel 2.1

Item {
    property var newElements;

    function numberOfScreens(num)
    {
       var elements = ' ';
       switch(num){
         case 1: if(newElements) newElements.destroy();
             rectangle.width = 659; break;
         case 2: elements = '
            import QtQuick 2.7
            import QtQuick.Controls 2.3
            import QtQuick.Layouts 1.0
            import QtQuick.Controls.Styles 1.4
            Rectangle {
                Rectangle {
                    x: 659/2
                    width: 659/2
                    height: 324
                    color: "#2e2f30"
                    border.color: "white"

                    Label {
                        x: 19
                        y: 0
                        width: 131
                        height: 19
                        font.family: "Arial"
                        font.pointSize: 12
                        color: "white"
                        text: "Актуальня позиция:"
                    }

                    Label {
                        id: lab_act_pos
                        x: 5
                        y: 23
                        width: 12
                        height: 13
                        color: "white"
                        font.family: "Arial"
                        font.pointSize: 9
                        text: lab_pos.text
                    }
              }
            }
        ';

        rectangle.width = 659/2;
        if(!newElements) newElements =  Qt.createQmlObject(elements, rowLayout);
        break;
     }
   }//end_func
}
