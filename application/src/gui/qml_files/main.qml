import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Controls 2.0


ApplicationWindow {
    id: mainWindow
    width: 1024
    height: 768
    title: "XFOIL OPTIMIZER"
    minimumWidth: 1023
    minimumHeight: 767
    maximumWidth: 1024
    maximumHeight: 768
    visible: true

    property color bright: "#85878A"
    property color dark: "#47494A"

    Frame {
        id: parametersFrame
        anchors.bottom: frameBaseChart.top
        anchors.bottomMargin: 13
        anchors.right: parent.right
        anchors.rightMargin: 198
        anchors.left: parent.left
        anchors.leftMargin: 32
        objectName: "parametersFrame"
        anchors.top: parent.top
        anchors.topMargin: 16
        spacing: 3

        InitialParameters{
            id: baseParametersBox
            anchors.right: targetParametersBox.left
            anchors.rightMargin: 23
            objectName: "baseParametersBox"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 19
            anchors.leftMargin: 8
            anchors.topMargin: 7
        }

        TargetValues {
            id: targetParametersBox
            x: 239
            anchors.topMargin: 7
            objectName: "targetParametersBox"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 19
            anchors.rightMargin: 349
        }

        FitnessParameters {
            id: fitnessBox
            objectName: "fitnessParameters"
            x: 459
            width: 195
            anchors.top: parent.top
            anchors.topMargin: 7
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 19

        }

        Button {
            id: runButton
            objectName: "runButton"
            anchors.top: parent.top
            anchors.topMargin: 120
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 40
            anchors.left: parent.left
            anchors.leftMargin: 668
            anchors.right: parent.right
            anchors.rightMargin: 0

            signal buttonClick(string name)

            MouseArea {
                id:mouseArea4
                anchors.rightMargin: 1
                anchors.bottomMargin: 0
                anchors.leftMargin: 0
                anchors.topMargin: 0
                anchors.top: parent.top
                anchors.fill: runButton
                onClicked: runButton.buttonClick("runButton")
            }

            Text {
                id: buttonText
                text: "RUN"
                anchors.centerIn: parent
                font.bold: true
                font.pointSize: 8
            }

        }

        Button {
            id: stopButton
            objectName:  "stopButton"
            anchors.left: parent.left
            anchors.leftMargin: 668
            anchors.bottom: parent.bottom
            anchors.bottomMargin: -2
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.top: runButton.bottom
            anchors.topMargin: 8

            signal buttonClick(string name)

            MouseArea {
                id:mouseArea6
                anchors.rightMargin: 1
                anchors.bottomMargin: 0
                anchors.leftMargin: 0
                anchors.topMargin: 0
                anchors.top: parent.top
                anchors.fill: stopButton
                onClicked: stopButton.buttonClick("stopButton")
            }

            Text {
                id: runButonText
                text: "STOP"
                anchors.centerIn: parent
                font.bold: true
                font.pointSize: 8
            }
        }
    }

    Buttons {
        anchors.left: parametersFrame.right
        anchors.leftMargin: 21
        anchors.bottom: frameBaseChart.top
        anchors.bottomMargin: 13
        anchors.rightMargin: -960
        anchors.topMargin: 16

    }


    Rectangle {
        id: frameBaseChart
        objectName: "frameBaseChart"
        color: "#CED1D2"
        radius: 13
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 284
        anchors.top: parent.top
        anchors.topMargin: 248
        anchors.right: parent.right
        anchors.rightMargin: 32
        anchors.left: parent.left
        anchors.leftMargin: 32
        border.width: 4

        BasePlot {

        }

        Label {
            id: label1
            text: qsTr("BASE PROFILE")
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 186
            anchors.right: parent.right
            anchors.rightMargin: 589
            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.top: parent.top
            anchors.topMargin: 13
            font.pointSize: 10
            font.bold: true
        }
    }

    Rectangle {
        id: frameOptimizeChart
        objectName: "frameOptimizeChart"
        color: "#CED1D2"
        radius: 13
        anchors.top: parent.top
        anchors.topMargin: 490
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 29
        anchors.right: parent.right
        anchors.rightMargin: 32
        anchors.left: parent.left
        anchors.leftMargin: 32
        border.width: 4

        OptimizedPlot {

        }

        Label {
            id: label2
            text: qsTr("OPTIMIZED PROFILE")
            anchors.right: parent.right
            anchors.rightMargin: 534
            anchors.left: parent.left
            anchors.leftMargin: 16
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 186
            font.bold: true
            font.pointSize: 10
            anchors.top: parent.top
            anchors.topMargin: 13
        }
    }

    ProgBar {
        anchors.topMargin: 6
        anchors.bottomMargin: 9

    }
}


