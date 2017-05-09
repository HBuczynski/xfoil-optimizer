import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2

Dialog {

    objectName: "optimizerDialog"
    visible: false
    title: "Optimizer settings"

    contentItem: Rectangle {
        objectName: "frame"
        color: "white"
        implicitWidth: 300
        implicitHeight: 400

        Button {
            id: applyButton
            width: 80
            height: 30

            objectName: "applyButton"
            anchors.top: parent.top
            anchors.topMargin:360
            anchors.left: parent.left
            anchors.leftMargin: 200

            signal buttonClick(string name)

            MouseArea {
                id:mouseArea4
                anchors.top: parent.top
                anchors.fill: applyButton
                onClicked: applyButton.buttonClick("applyButton")
            }

            Text {
                id: buttonText
                text: "APPLY"
                anchors.centerIn: parent
                font.pointSize: 8
            }

        }

        Button {
            id: cancelButton
            width: 80
            height: 30
            objectName: "cancelButton"
            anchors.top: parent.top
            anchors.topMargin:360
            anchors.right: applyButton.left
            anchors.rightMargin: 16

            signal buttonClick(string name)

            MouseArea {
                id:cancelButtonArea
                anchors.top: parent.top
                anchors.fill: cancelButton
                onClicked: cancelButton.buttonClick("cancelButton")
            }

            Text {
                id: buttonText2
                text: "CANCEL"
                anchors.centerIn: parent
                font.pointSize: 8
            }

        }

        GroupBox {
            id: groupBox1
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width - 34
            height: parent.height - 55
            title: qsTr("Settings")

        }

    }
}

