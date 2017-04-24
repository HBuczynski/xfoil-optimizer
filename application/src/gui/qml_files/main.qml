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

    Frame {
        id: parametersFrame
        x: 336
        y: 18
        width: 643
        height: 243
        spacing: 3

        InitialParameters{
            id: baseParametersBox
            anchors.right: parent.right
            anchors.rightMargin: 386
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 19
            anchors.leftMargin: 33
            anchors.topMargin: 7
        }

        TargetValues {
            id: targetParametersBox
            anchors.left: parent.left
            anchors.leftMargin: 397
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 19
            anchors.rightMargin: 19
        }
    }

    Frame {
        id: buttonFrame
        x: 32
        width: 145
        height: 178
        anchors.top: parent.top
        anchors.topMargin: 18
        anchors.right: parametersFrame.left
        anchors.rightMargin: 159

        Button {
            id: button1
            x: 47
            width: 120
            height: 40
            text: qsTr("Load Profile")
            anchors.top: parent.top
            anchors.topMargin: 6
            anchors.horizontalCenterOffset: 0
            anchors.horizontalCenter: parent.horizontalCenter
            checkable: false
            checked: false
        }

        Button {
            id: button2
            x: 0
            y: 55
            text: qsTr("Optimizer Settings")
            anchors.verticalCenter: parent.verticalCenter
        }

        Button {
            id: button3
            x: 0
            y: 108
            width: 120
            height: 40
            text: qsTr("Run")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 6
        }
    }

    BusyIndicator {
        id: busyIndicator
        x: 835
        y: 601
        width: 88
        height: 92
    }

    FitnessParameters {
        id: fitnessBox
        x: 779
        y: 277
        width: 200
        height: 220
    }

    Frame {
        id: frameBaseChart
        x: 32
        y: 295
        width: 728
        height: 202
    }

    Frame {
        id: frameOptimizeChart
        x: 32
        y: 539
        width: 728
        height: 203
    }

    Label {
        id: label1
        text: qsTr("BASE PROFILE")
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 479
        anchors.left: parent.left
        anchors.leftMargin: 32
        anchors.top: parent.top
        anchors.topMargin: 273
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
}


