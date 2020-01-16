import QtQuick 2.3
import QtQuick.Controls 2.4
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.11

Item {
    id: mainWindow
    property real alt
    property real latNMEA
    property real lonNMEA
    property real latRAW : 48.86666 //test affichage RAW sans calcul ni module
    property real lonRAW : 2.333333
    property var ephemerisData : ({svid: 0, iodc: 1, tgd: 2, toc: 3, af0: 4, af1: 5, af2: 6, iode: 7, crs: 8, dn: 9, m0: 10, cuc: 11, e: 12, sqrtA: 13, toe: 14, fit: 22, cic: 15, omega0: 16, i0: 17, crc: 18, omega: 19, omegap: 20, idot: 21})
    property int weekNumber

    function addData(carray){
        console.log(carray)
        ephemerisData.svid = carray[0]
        ephemerisData.iodc = carray[1]
        ephemerisData.tgd = carray[2]
        ephemerisData.toc = carray[3]
        ephemerisData.af0 = carray[4]
        ephemerisData.af1 = carray[5]
        ephemerisData.af2 = carray[6]
        ephemerisData.iode = carray[7]
        ephemerisData.crs = carray[8]
        ephemerisData.dn = carray[9]
        ephemerisData.m0 = carray[10]
        ephemerisData.cuc = carray[11]
        ephemerisData.e = carray[12]
        ephemerisData.sqrtA = carray[13]
        ephemerisData.toe = carray[14]
        ephemerisData.fit = carray[15]
        ephemerisData.cic = carray[16]
        ephemerisData.omega0 = carray[17]
        ephemerisData.i0 = carray[18]
        ephemerisData.crc = carray[19]
        ephemerisData.omega = carray[20]
        ephemerisData.omegap = carray[21]
        ephemerisData.idot = carray[22]
        listeSatellites.append(ephemerisData)
    }

    function clearData(){
        listeSatellites.clear()
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
            Tab2Infographie{
                id:infographie
                anchors.top: tableau.bottom
                anchors.left: tableau.left
                weekNumber:  mainWindow.weekNumber
            }
        }

        Item {
            id: thirdTab
        }
    }
}
