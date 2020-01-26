import QtQuick 2.3
import QtQuick.Controls 2.4
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.11
Item {
    property int weekNumber
    property real latNMEA
    property real lonNMEA
    property real timeGMT
    property int fontSize: 14
    width: parent.width
    height: 60*parent.height/100
    anchors.margins: 20

    Column{
        width: parent.width/2
        height: parent.height
        spacing: 10
        Text{
            id:nbSat
            font.pointSize: fontSize
            text: "There is " + tableau.rowCount + " visible satellites"
        }
        Text{
            id:wN
            font.pointSize: fontSize
            text: "The GPS week number is : " + weekNumber
        }
        Text{
            id:time
            font.pointSize: fontSize
            text:"It is : " + timeGMT + " GMT"
        }
        Text{
            id:latitude
            font.pointSize: fontSize
            text:"NMEA given latitude: " + latNMEA
        }
        Text{
            id:longitude
            font.pointSize: fontSize
            text:"NMEA given longitude: " + lonNMEA
        }
    }

}

