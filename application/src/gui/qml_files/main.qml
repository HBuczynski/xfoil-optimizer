import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Controls 2.0


ApplicationWindow {
    id: mainWindow
    width: 1024
    height: 768
    title: "XFOIL OPTIMIZER"
    minimumWidth: 800
    minimumHeight: 480
    maximumWidth: 1024
    maximumHeight: 768
    visible: true

    property color bright: "#85878A"
    property color dark: "#47494A"

    Frame {
        id: parametersFrame
        objectName: "parametersFrame"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 507
        anchors.top: parent.top
        anchors.topMargin: 18
        anchors.right: parent.right
        anchors.rightMargin: 45
        anchors.left: parent.left
        anchors.leftMargin: 336
        spacing: 3

        InitialParameters{
            id: baseParametersBox
            objectName: "baseParametersBox"
            anchors.right: parent.right
            anchors.rightMargin: 386
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 19
            anchors.leftMargin: 33
            anchors.topMargin: 7
        }

        TargetValues {
            id: targetParametersBox
            objectName: "targetParametersBox"
            anchors.left: parent.left
            anchors.leftMargin: 397
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 19
            anchors.rightMargin: 19
        }
    }

    Buttons {

    }

    BusyIndicator {
        id: busyIndicator
        objectName: "busyIndicator"
        x: 855
        y: 338
        width: 88
        height: 92

        running: true
    }

    FitnessParameters {
        id: fitnessBox
        objectName: "fitnessParameters"
        x: 799
        y: 539
        width: 200
        height: 220
    }

    Label {
        id: label1
        text: qsTr("BASE PROFILE")
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 501
        anchors.left: parent.left
        anchors.leftMargin: 32
        anchors.top: parent.top
        anchors.topMargin: 251
    }

    Label {
        id: label2
        text: qsTr("OPTIMIZED PROFILE")
        anchors.top: parent.top
        anchors.topMargin: 517
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 235
        anchors.left: parent.left
        anchors.leftMargin: 32
    }

    Rectangle {
        id: rectangle1
        x: 32
        y: 280
        width: 728
        height: 220
        color: "#ffffff"
        radius: 13
        border.width: 4

        BasePlot {

        }
    }

    Rectangle {
        id: rectangle2
        x: 32
        y: 539
        width: 728
        height: 220
        color: "#ffffff"
        radius: 13
        border.width: 4
        OptimizedPlot {
        }
    }
}


