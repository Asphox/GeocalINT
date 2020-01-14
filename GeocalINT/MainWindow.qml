import QtQuick 2.3
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11


Item {
    id: mainWindow
    property real alt
    property real latNMEA
    property real lonNMEA
    property real latRAW : 48.86666 //test affichage RAW sans calcul ni module
    property real lonRAW : 2.333333

    /*MenuBar{
        id:embeddedMenu
    }*/
    TabBar {
        id: bar
        width: parent.width
        TabButton {
            text: qsTr("Map")

        }
        TabButton {
            text: qsTr("GNSS Output")
        }
        TabButton {
            text: qsTr("Other")
        }
    }
    StackLayout {
        width: parent.width
        height: parent.height
        anchors.top:bar.bottom
        currentIndex: bar.currentIndex

        Map{
            id:mapTab
            latNMEA: parent.latNMEA
            lonNMEA: parent.lonNMEA
            latRAW: parent.latRAW
            lonRAW: parent.lonNMEA
        }

        Item {
            id: redTab
            Rectangle{
                anchors.fill: parent
                color: 'red'
            }
        }
        Item {
            id: otherTab
        }
    }
}
