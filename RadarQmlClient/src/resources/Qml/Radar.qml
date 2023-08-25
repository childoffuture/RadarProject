import QtQuick 2.0


//id: baseItem
//anchors.fill: parent
Item {
    Repeater {
        model : 50
        Rectangle {
            anchors.centerIn: parent
            width: 50 + 30 * index
            height: width
            radius: width / 2
            border.color: "green"
            color: "transparent"
            border.width: 1
        }
    }

    Rectangle {
        border.color: "green"
        color: "transparent"
        height: 1
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.verticalCenter
    }

    Rectangle {
        border.color: "green"
        color: "transparent"
        width: 1
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.horizontalCenter
    }
}
