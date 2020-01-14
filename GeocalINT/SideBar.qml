import QtQuick 2.3
import QtPositioning 5.13
import QtLocation 5.13
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Item {
    width:parent.width
    height: parent.height
    property real zoom : sliderZoom.value
    property real rot : sliderRot.value
    visible: true


    Button{
        id: openButton
        height: parent.height
        width: parent.width*0.03
        visible: true
        Text {
            rotation: 270
            anchors.centerIn: parent
            text: "Open"
        }
        onClicked: {
            closeButton.visible = true
            openButton.visible = false
            popupControls.visible = true
        }
    }

    Button{
        id: closeButton
        height: openButton.height
        width: openButton.width
        x : popupControls.width
        visible: false
        Text {
            rotation: 270
            anchors.centerIn: parent
            text: "Close"
        }
        onClicked:{
            closeButton.visible = false
            openButton.visible = true
            popupControls.visible = false
        }
    }


    Rectangle {
        id: popupControls
        width: parent.width*0.15
        height: parent.height
        opacity: 1
        visible: false
        //closePolicy: Popup.CloseOnPressOutside
        Column{
            spacing: 10
            height: parent.height
            width: parent.width*0.9
            anchors.centerIn: parent
            Slider{     //Slider pour le zoom
                id: sliderZoom
                width: parent.width
                from: 3
                to: 20
                value: 14
            }

            Slider{     //Slider pour la rotation de la map
                id: sliderRot
                width: parent.width
                from:0
                to: 360
                value:0
            }

            Button{
                id: refreshPosition
                width: parent.width
                text: "Refresh"
            }

            CheckBox{
                id: constRefresh
                width: parent.width
                text: "Constant"
            }
        }
    }
}
