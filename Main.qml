import QtQuick
import QtQuick.Controls
import EQ 1.0

Window {
    width: 1080
    height: 750
    visible: true
    color: "#1a1a2e"

    property real volume: 0

    Connections {
           target: audioProcessor

           function onVolumeChanged(value) {
               volume = value
           }
       }


    WaveformView {

        objectName: "waveform"
         id: waveform
        anchors.fill: parent

    }

    Column {

        anchors.right: parent.right
        anchors.top: parent.top

        spacing: 10


        Text {
            text: "Smoothing"
            color: "white"
        }


        Slider {

            id: smoothSlider

            from: 1
            to: 20

            value: 1


            onValueChanged:
            {
                waveform.smoothing = Math.round(value)
            }
        }

    }

    Rectangle {
        anchors.right: parent.right
        anchors.bottom: parent.bottom

            width: 40
            height: 300

            color: "gray"


            Rectangle {
                width: parent.width
                height: parent.height * volume

                anchors.bottom: parent.bottom

                color: "green"
            }
        }

}
