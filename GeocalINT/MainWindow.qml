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
    property QtObject listeSatellites
    Component.onCompleted: console.log(listeSatellites)
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
            id: secondTab
            Tableau{
                id:tableau
                model: listeSatellites
            }
        }
        Item {
            id: otherTab
        }
    }
}
