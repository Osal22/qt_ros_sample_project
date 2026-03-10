import QtQuick
import QtQuick.Layouts
import MainModule 1.0

ColumnLayout {
    property string title: ""
    property alias model: listView.model
    property color headerColor: "blue"

    spacing: 0

    // 1. Header Section
    Rectangle {
        Layout.fillWidth: true
        height: 30
        color: headerColor
        
        Text { 
            text: title
            anchors.centerIn: parent 
            color: "white"
            font.bold: true 
        }
    }

    ListView {
        id: listView
        Layout.fillWidth: true
        Layout.fillHeight: true
        clip: true
        
        delegate: Rectangle {
            id: itemDelegate
            width: listView.width
            height: 35
            border.color: '#bcda15'
            color: itemMouseArea.containsMouse ? "#eef6ee" : "white"

            Text { 
                text: modelData
                anchors.centerIn: parent
                font.family: "Monospace"
            }

            // Move MouseArea here so 'modelData' refers to the row item
            MouseArea {
                id: itemMouseArea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    // This calls the C++ function with the text of the clicked row
                    DataInterfaceNode.selectFault(modelData)
                }
            }
        }
    }
}