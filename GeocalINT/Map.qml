import QtQuick 2.3
import QtPositioning 5.13
import QtLocation 5.13
import QtQuick.Controls 2.5


Item {
    id: item
    objectName: "item"
    property real alt
    property real latNMEA
    property real lonNMEA
    property real latRAW
    property real lonRAW


    Plugin{
        id: mapPlugin
        name: "osm"
        PluginParameter { name: "osm.mapping.providersrepository.disabled"; value: "true"} //Parametre pour empecher OSM de fetch n'importe où
        PluginParameter { name: "osm.mapping.highdpi_tiles"; value: "true"} //Tiles in HD
        PluginParameter { name: "osm.mapping.host"; value: "http://osm.tile.server.address/" }
    }
    Map{            //Intégration d'une carte, fournie par le plugin, ici Open Street Map
        id: mapViewer
        objectName: "mapViewer"
        anchors.fill: parent
        plugin: mapPlugin

        /*MapCircle{      //Pinpoint de la position
            id: pinPoint
            objectName: "circle"
            color: "red"
            radius: 1
            center: QtPositioning.coordinate(lat,lon)
        }*/

        MapQuickItem {
            id: nmea
            sourceItem: Image{source :"pinNMEA.png"}
            coordinate :QtPositioning.coordinate(latNMEA,lonNMEA)
            opacity:1.0
            anchorPoint: Qt.point(sourceItem.width/2, sourceItem.height)
        }

        MapQuickItem {
            id: raw
            sourceItem: Image{source :"pinRAW.png"}
            coordinate :QtPositioning.coordinate(latRAW,lonRAW)
            opacity:1.0
            anchorPoint: Qt.point(sourceItem.width/2, sourceItem.height)
        }

        SideBar{        //Appel des sliders zoom et rotation
            id: side
        }
        zoomLevel: side.zoom
        bearing: side.rot
        center: QtPositioning.coordinate(lat, lon)
    }
}


