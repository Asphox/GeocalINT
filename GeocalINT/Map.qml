import QtQuick 2.3
import QtPositioning 5.13
import QtLocation 5.13
import QtQuick.Controls 2.5


Item {
    id: item
    property real lat
    property real lon
    property real alt


    Plugin{
        id: mapPlugin
        name: "osm"
        PluginParameter { name: "osm.mapping.providersrepository.disabled"; value: "true"} //Parametre pour empecher OSM de fetch n'importe où
        PluginParameter { name: "osm.mapping.highdpi_tiles"; value: "true"} //Tiles in HD
        PluginParameter { name: "osm.mapping.host"; value: "http://osm.tile.server.address/" }
    }
    Map{
        id: mapViewer
        anchors.fill: parent
        plugin: mapPlugin
        MapCircle{
            id: circle
            color: "red"
            radius: 100000
            center: QtPositioning.coordinate(lat,lon)
        }

        SideBar{id: side}
        zoomLevel: side.zoom
        bearing: side.rot

        center: QtPositioning.coordinate(lat, lon)
    }

    function onNMEAFrameGLL(plat,plon){
        item.lat=plat/100
        item.lon=plon/100

        console.log(lat)
        console.log(item.lat)
        console.log(lon)

    }
}


