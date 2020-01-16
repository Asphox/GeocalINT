import QtQuick 2.3
import QtQuick.Controls 2.4
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.11
Item {
    property int weekNumber
    width: parent.width
    height: parent.height/2

    Column{
        width: parent.width/2
        height: parent.height
        spacing: 10
        Text{
            id:nbSat
            text: "Il y a " + tableau.rowCount + " satellites visibles"
        }
        Text{
            id:wN
            text: "Nous sommes a la semaine GPS : " + weekNumber
        }
        Text{
            id:time
            text:"Il est : " + " GMT"
        }

    }

}

