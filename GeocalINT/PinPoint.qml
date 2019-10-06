import QtQuick 2.3
import QtPositioning 5.13
import QtLocation 5.13
import QtQuick.Controls 2.5

Item {
    property real latitude
    property real longitude
    property real altitude

    MapCircle{
        color: "red"
        radius: 100000
        center: QtPositioning.coordinate(latitude, longitude)
    }
}
