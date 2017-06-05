import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
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

        Text {
            id: text1
            height: 24
            text: qsTr("Generation Count: ")
            transformOrigin: Item.Center
            anchors.left: parent.left
            anchors.leftMargin: 40
            anchors.top: parent.top
            anchors.topMargin: 32
            font.pixelSize: 16
        }

        TextField {
            id: textField1
            objectName: "generationCount"
            transformOrigin: Item.Center
            anchors.right: parent.right
            anchors.rightMargin: 40
            anchors.top: parent.top
            anchors.topMargin: 32
            font.pixelSize: 16
            width: 65
            text: "20"

            style: TextFieldStyle {
                                textColor: "black"
                                }
        }


        Text {
            id: text2
            x: -6
            y: -5
            height: 24
            text: qsTr("Population Size: ")
            anchors.left: parent.left
            anchors.topMargin: 71
            anchors.top: parent.top
            anchors.leftMargin: 40
            font.pixelSize: 16
            anchors.rightMargin: 107
            anchors.right: parent.right
        }

        TextField {
            id: textField2
            objectName: "populationSize"
            transformOrigin: Item.Center
            anchors.right: parent.right
            anchors.rightMargin: 40
            anchors.top: parent.top
            anchors.topMargin: 71
            font.pixelSize: 16
            width: 65
            text: "100"

            style: TextFieldStyle {
                                textColor: "black"
                                }
        }

        Text {
            id: text3
            x: -6
            y: -5
            height: 24
            text: qsTr("Mutation Rate: ")
            anchors.left: parent.left
            anchors.topMargin: 110
            anchors.top: parent.top
            anchors.leftMargin: 40
            font.pixelSize: 16
            anchors.rightMargin: 107
            anchors.right: parent.right
        }

        TextField {
            id: textField3
            objectName: "mutationRate"
            transformOrigin: Item.Center
            anchors.right: parent.right
            anchors.rightMargin: 40
            anchors.top: parent.top
            anchors.topMargin: 110
            font.pixelSize: 16
            width: 65
            text: "0.05"

            style: TextFieldStyle {
                                textColor: "black"
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

