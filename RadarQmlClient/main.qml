import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    id: mainWindow
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Radar {
        id: baseItem
        anchors.fill: parent

        Repeater
        {
            anchors.fill: parent
            model: listModel
            delegate:
            Rectangle {
                id: rect
                width: 10
                color: object_color
                height: width
                radius: width / 2
                x : (x_pos + 1) * mainWindow.width / 2 - radius
                y : (1 - y_pos) * mainWindow.height / 2 - radius
                Text {
                    id: txt
                    x: parent.x + 10
                    y: parent.y + 10
                    anchors.left: parent.right
                    anchors.top: parent.bottom
                    text: text_data + " (x: " + x_pos + " y: " + y_pos + ")"
                }
            }
        }
    }
}
