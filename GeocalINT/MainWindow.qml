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
    property var listeTest : ({svid: 0, iodc: 1, tgd: 2, toc: 3, af0: 4, af1: 5, af2: 6, iode: 7, crs: 8, dn: 9, m0: 10, cuc: 11, e: 12, sqrtA: 13, toe: 14, fit: 22, cic: 15, omega0: 16, i0: 17, crc: 18, omega: 19, omegap: 20, idot: 21})
    //Component.onCompleted: console.log(listeTest)

    function readValue(carray){
        console.log("SUUUUUUUS")
        console.log(carray)
        for (var i=0; i<carray.length;i++){
            console.log("test",carray[i])
        }
    }

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
