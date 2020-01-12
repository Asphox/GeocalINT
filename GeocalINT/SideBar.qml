import QtQuick 2.3
import QtPositioning 5.13
import QtLocation 5.13
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Item {
    width:parent.width
    height: parent.height
    anchors.fill: parent
    property double zoom : sliderZoom.value
    property double rot : sliderRot.value
    property double latitude
    property double longitude

    Rectangle{
        id: containerPopup
        width: parent.width*0.15
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

                Slider{     //Slider pour le zoom
                    id: sliderZoom
                    width: parent.width
                    from: 3
                    to: 20
                    value: 14
                    signal sliderZoomMoved
                    //onMoved: console.log(value)

                }

                Slider{     //Slider pour la rotation de la map
                    id: sliderRot
                    width: parent.width
                    from:0
                    to: 360
                    value:0

                }

                Column{    //Not used yet, a click on the refresh button will actualise the position, and the checkbox will refresh
                    width: parent.width
                    Button{
                        id: refreshPosition
                        width: parent.width
                        text: "Refresh"

                        onClicked: {
                        }

                    }

                    CheckBox{
                        id: constRefresh
                        width: parent.width
                        text: "Constant"
                    }
                }
            }
        }
    }

    Rectangle{
        x:parent.width*0.15
        y:0
        width: parent.width*0.03
        height: parent.height
        visible: false

        Popup{
            id: popupClose
            width: parent.width
            height: parent.height
            opacity: 0.7
            closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideThis

            MouseArea{
                id: mousePopOff
                width: parent.width
                height: parent.height
                onClicked:{
                    popupClose.close()
                    popupControls.close()
                }
                Text {
                    id: textClose
                    text: qsTr("Close")
                    rotation: 270
                    anchors.centerIn: parent
                }
            }
        }
    }

    Rectangle{
        color: "white"
        opacity: 0.7
        border.width:1
        width: parent.width*0.03
        height: parent.height

        MouseArea{
            id: mousePopUp
            anchors.fill: parent
            onClicked: {
                popupClose.open()
                popupControls.open()
            }
            Text {
                id: textOpen
                text: qsTr("Open")
                rotation: 270
                anchors.centerIn: parent
            }
        }
    }
}
