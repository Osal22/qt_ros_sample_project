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
            border.color: '#4e5a07'
            color: itemMouseArea.containsMouse ? '#16cc16' : "grey"

            Row {
                anchors.fill: parent
                anchors.leftMargin: 10
                spacing: 10
                // REMOVED: verticalAlignment here was causing the error

                // The Index Text
                Text {
                    text: (index + 1) + "." 
                    font.bold: true
                    color: "#666666"
                    width: 25 
                    anchors.verticalCenter: parent.verticalCenter // This handles the alignment
                }

                // The Message Text
                Text {
                    text: modelData
                    font.family: "Monospace"
                    anchors.verticalCenter: parent.verticalCenter // This handles the alignment
                    
                    // If you wanted internal alignment, it would go here:
                    // verticalAlignment: Text.AlignVCenter 
                }
            }

            MouseArea {
                id: itemMouseArea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    DataInterfaceNode.selectFault(modelData)
                }
            }
        }
    }
}