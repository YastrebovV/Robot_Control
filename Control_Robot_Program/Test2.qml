import QtQuick 2.5
import QtQuick.Controls 1.4

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    /* Номер создаваемой кнопки, для её визуальной идентификации
     * при демонстрации проекта
     */
    property int number: 0

    /* Строка с полем, где отображается индекс нажатой динамической кнопки,
     * кнопкой для создания динамических кнопок,
     * и кнопкой для удаления динамических кнопок по индексу
     * */
    Row {
        id: row
        // Задаём размеры строки и прибиваем к верхней части окна приложения
        height: 50
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        // Задаём размещение поля с индексом кнопки
        Rectangle {
            width: (parent.width / 5)
            height: 50

            // Устанавливаем текстовое поле для размещения индекса кнопки
            Text {
                id: textIndex
                anchors.fill: parent
                text: ""
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }

        // Кнопка для создания динамических кнопок
        Button {
            id: button1
            text: qsTr("Create Button")
            width: (parent.width / 5)*2
            height: 50

            /* По клику по кнопке добавляем в model ListView
             * объект, с заданными параметрами
             * */
            onClicked: {
                listModel.append({idshnik: "Button " + (++number)})

            }
        }

        // Кнопка для удаления динамических кнопок
        Button {
            id: button2
            text: qsTr("Delete Button")
            width: (parent.width / 5)*2
            height: 50

            // Удаляем кнопку по её индексу в ListView
            onClicked: {
                if(textIndex.text != ""){
                    listModel.remove(textIndex.text)
                    textIndex.text = "" // Обнуляем текстовое поле с индексом
                }
            }
        }
    }

    // ListView для представления данных в виде списка
    ListView {
        id: listView1
        // Размещаем его в оставшейся части окна приложения
        anchors.top: row.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        /* в данном свойстве задаём вёрстку одного объекта
         * который будем отображать в списке в качестве одного элемента списка
         * */
        delegate: Item {
            id: itemm
            anchors.left: parent.left
            anchors.right: parent.right
            height: 40

            // В данном элементе будет находиться одна кнопка
            Button {
                anchors.fill: parent
                anchors.margins: 5

                /* самое интересное в данном объекте
                 * задаём свойству text переменную, по имени которой будем задавать
                 * свойства элемента
                 * */
                text: idshnik

                // По клику по кнопке отдаём в текстовое поле индекс элемента в ListView
                onClicked: {
                    textIndex.text = index
                }
            }
        }

        // Сама модель, в которой будут содержаться все элементы
        model: ListModel {
            id: listModel // задаём ей id для обращения
        }
    }
}
