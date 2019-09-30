import QtQuick 2.3
import QtPositioning 5.13
import QtLocation 5.13

Item {
    Plugin{
        id: mapPlugin
        name: "osm"
        PluginParameter { name: "osm.mapping.providersrepository.disabled"; value: "true"} //Parametre pour empecher OSM de fetch n'importe où
        PluginParameter { name: "osm.mapping.highdpi_tiles"; value: "true"} //Tiles in HD
        PluginParameter { name: "osm.mapping.host"; value: "http://osm.tile.server.address/" }
    }
    Map{
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(59.91, 10.75)
        zoomLevel: 14
    }
}
