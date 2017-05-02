import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Controls 2.0

Frame {
    id: buttonFrame
    objectName: "buttonFrame"
    x: 32
    width: 145
    height: 178
    anchors.top: parent.top
    anchors.topMargin: 18
    anchors.right: parametersFrame.left
    anchors.rightMargin: 159

    //buttons names
    property string buttonName1: "button1"
    property string buttonName2: "button2"
    property string buttonName3: "button3"

    Button {
        id: button1
        objectName: buttonName1
        x: 47
        width: 120
        height: 40
        text: qsTr("Load Profile")
        anchors.top: parent.top
        anchors.topMargin: 6
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter

        signal buttonClick(string name)

        MouseArea {
            id:mouseArea1
            anchors.fill: button1
            onClicked: button1.buttonClick(buttonName1)
        }
    }

    Button {
        id: button2
        objectName: buttonName2
        x: 0
        y: 55
        text: qsTr("Optimizer Settings")
        anchors.verticalCenter: parent.verticalCenter

        signal buttonClick(string name)

        MouseArea {
            id:mouseArea2
            anchors.fill: button2
            onClicked: button2.buttonClick(buttonName2)
        }
    }

    Button {
        id: button3
        objectName: buttonName3
        x: 0
        y: 108
        width: 120
        height: 40
        text: qsTr("Run")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 6

        signal buttonClick(string name)

        MouseArea {
            id:mouseArea3
            anchors.fill: button3
            onClicked: button3.buttonClick(buttonName3)
        }
    }
}

