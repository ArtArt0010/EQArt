import QtQuick
import QtQuick.Controls
import EQ 1.0

Window {
    width: 1080
    height: 750
    visible: true
    color: "#1a1a2e"
    property bool flag: false

    property real volume: 0

    Connections {
           target: audioProcessor

           function onVolumeChanged(value) {
               volume = value
           }
           function onSpectrumChanged(spectrum) {
                   spectrumView.setSpectrum(spectrum)
               }
       }


    WaveformView {

        objectName: "waveform"
        id: waveform
        visible: !flag
        anchors.fill: parent

    }

    SpectrumView {
            id: spectrumView
            visible: flag
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

        Button{
            id: modeButton
            width: 80
            height: 30
              hoverEnabled: false

            background: Rectangle{      // фон кнопки
                        anchors.fill: parent
                       // color: "#330645"// цвет фона кнопки
                        color: modeButton.down ? "#330645" : "#410559"
                        border.color: "#01a3a4"         // цвет границы
                        radius: 5
            }

            text: "Режим"

            onClicked: flag = !flag
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
