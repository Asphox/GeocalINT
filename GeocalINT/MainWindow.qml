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
    property var suus:[2,123,2.5,1892,-1829,2901809,-19821,12,12980.192,12.99,121,2190.11,1.0001,5283,12111,0,21111,31333,1412,99100.11,1991,42,12]
    //Component.onCompleted: console.log(listeTest)

    function ephemerisData(carray){
        console.log("SUUUUUUUS")
        console.log(carray)
        listeTest.svid = carray[0]
        listeTest.iodc = carray[1]
        listeTest.tgd = carray[2]
        listeTest.toc = carray[3]
        listeTest.af0 = carray[4]
        listeTest.af1 = carray[5]
        listeTest.af2 = carray[6]
        listeTest.iode = carray[7]
        listeTest.crs = carray[8]
        listeTest.dn = carray[9]
        listeTest.m0 = carray[10]
        listeTest.cuc = carray[11]
        listeTest.e = carray[12]
        listeTest.sqrtA = carray[13]
        listeTest.toe = carray[14]
        listeTest.fit = carray[15]
        listeTest.cic = carray[16]
        listeTest.omega0 = carray[17]
        listeTest.i0 = carray[18]
        listeTest.crc = carray[19]
        listeTest.omega = carray[20]
        listeTest.omegap = carray[21]
        listeTest.idot = carray[22]

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
            ListModel{
                id:listeSatellites
            }

            Button{
                onClicked:{
                    ephemerisData(suus)
                    listeSatellites.append(listeTest)
                }
            }
        }

        Item {
            id: otherTab
        }
    }
}
