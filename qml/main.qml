import QtQuick
import QtQuick.Layouts
import MainModule 1.0

Window {
    width: 900; height: 500
    visible: true
    title: "System Status Monitor"
    color: '#332525' 
    RowLayout {
        anchors.fill: parent
        anchors.margins: 10 
        spacing: 15

        StatusTable { 
            title: "Faults"; 
            model: DataInterfaceNode.faultList; 
            headerColor: "#ff4444" 
        }

        // Table 2: Latent Faults
        StatusTable { 
            title: "Latent Faults"; 
            model: DataInterfaceNode.latentFaultList; 
            headerColor: "#ffbb33" 
        }

        // Table 3: No Faults
        StatusTable { 
            title: "Normal Operations"; 
            model: DataInterfaceNode.noFaultList; 
            headerColor: "#00C851" 
        }
    }

    ColumnLayout {
    anchors.fill: parent
    
    RowLayout {
        // ... your 3 StatusTables here ...
    }

    // New Detail Box
    Rectangle {
        Layout.fillWidth: true
        Layout.preferredHeight: 100
        color: "#333333"
        radius: 5

        Column {
            anchors.fill: parent
            anchors.margins: 10
            spacing: 5

            Text { 
                text: "Diagnostic Details:" 
                color: '#db1717'; font.bold: true
            }

            Text {
                text: DataInterfaceNode.selectedInfo // Bind to the C++ property
                color: "white"
                font.pixelSize: 14
                wrapMode: Text.WordWrap
                width: parent.width
            }
        }
    }
}
}