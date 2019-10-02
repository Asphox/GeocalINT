import QtQuick 2.3
import QtPositioning 5.13
import QtLocation 5.13
import QtQuick.Controls 2.5


Item {


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
        center: QtPositioning.coordinate(59.91, 10.75)
        zoomLevel: sliderZoom.value
        bearing: sliderRot.value
        MapCircle{
            pointer
        }
    }

    Button {
        id: openButton
        text: "Open"
        onClicked: popupControls.open()
        padding: 10
    }


    Rectangle{
        id: containerPopup
        width: parent.width*0.2
        height: parent.height
        visible: false

        Popup {
            id: popupControls
            width: parent.width
            height: parent.height
            opacity: 1
            closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideThis

            Column{
                spacing: 10
                height: parent.height
                width: parent.width

                Slider{
                    id: sliderZoom
                    width: parent.width
                    from: 1
                    to: 20
                    value: 14
                }

                Slider{
                    id: sliderRot
                    width: parent.width
                    from:0
                    to: 360
                    value:0
                }

                Row{
                    Button{
                        id: refreshPosition
                        text: "Refresh"

                        signal refreshPos()
                    }

                    CheckBox{
                        id: constRefresh
                        text: "Constant"
                        signal constRefreshPos()
                    }
                }


                Button{
                    id: closeButton
                    text: "Close"
                    onClicked: popupControls.close()
                }
            }
        }
    }

}


