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
        y: -12
        width: 120
        height: 40
        text: qsTr("Load Profile")
        anchors.bottom: button2.top
        anchors.bottomMargin: 15
        anchors.horizontalCenterOffset: -1
        anchors.horizontalCenter: parent.horizontalCenter

        signal buttonClick(string name)

        MouseArea {
            id:mouseArea1
            anchors.top: parent.top
            anchors.fill: button1
            onClicked: button1.buttonClick(buttonName1)
        }
    }

    Button {
        id: button2
        objectName: buttonName2
        text: qsTr("Optimizer Settings")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        signal buttonClick(string name)
        x: 0
        y: 34

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
        width: 120
        height: 40
        text: qsTr("Plot")
        anchors.top: button2.bottom
        anchors.topMargin: 15
        anchors.horizontalCenter: parent.horizontalCenter

        signal buttonClick(string name)

        MouseArea {
            id:mouseArea3
            anchors.top: parent.top
            anchors.fill: button3
            onClicked: button3.buttonClick(buttonName3)
        }
    }
}

