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
            onClicked: side.visible = true
        }
        TabButton {
            text: qsTr("GNSS Output")
            onClicked: side.visible = false
        }
        TabButton {
            text: qsTr("Other")
            onClicked: side.visible = false
        }
    }
    StackLayout {
        width: parent.width
        height: parent.height
        anchors.top:bar.bottom
        currentIndex: bar.currentIndex

        Item {
            id: firstTab
            Map{
                id:mapTab
                latNMEA: mainWindow.latNMEA
                lonNMEA: mainWindow.lonNMEA
                latRAW: mainWindow.latRAW
                lonRAW: mainWindow.lonRAW
                zoom: side.zoom
                rot: side.rot
            }
            SideBar{        //Appel des sliders zoom et rotation
                id: side

            }
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
