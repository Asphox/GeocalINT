import QtQuick 2.3
import QtPositioning 5.13
import QtLocation 5.13
import QtQuick.Controls 2.5


Item {
    id: item
    objectName: "item"
    property real alt
    property real lat
    property real lon


    Plugin{
        id: mapPlugin
        name: "osm"
        PluginParameter { name: "osm.mapping.providersrepository.disabled"; value: "true"} //Parametre pour empecher OSM de fetch n'importe où
        PluginParameter { name: "osm.mapping.highdpi_tiles"; value: "true"} //Tiles in HD
        PluginParameter { name: "osm.mapping.host"; value: "http://osm.tile.server.address/" }
    }
    Map{
        id: mapViewer
        objectName: "mapViewer"
        anchors.fill: parent
        plugin: mapPlugin

        MapCircle{
            id: circle
            objectName: "circle"
            color: "red"
            radius: 100
            center: QtPositioning.coordinate(lat,lon)
        }

        SideBar{
            id: side
        }
        zoomLevel: side.zoom
        bearing: side.rot

        center: QtPositioning.coordinate(lat, lon)
    }
}


