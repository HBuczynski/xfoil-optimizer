import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1

GroupBox {
    id: groupBox1
    x: 716
    y: 316
    width: 200
    height: 200
    title: qsTr("FITNESS")

    Text {
        id: text1
        height: 24
        color: "#0e26d6"
        text: qsTr("CL max")
        styleColor: "#f12121"
        transformOrigin: Item.Center
        anchors.right: parent.right
        anchors.rightMargin: 107
        anchors.left: parent.left
        anchors.leftMargin: 27
        anchors.top: parent.top
        anchors.topMargin: 32
        font.pixelSize: 12
    }

    Text {
        id: text2
        x: -6
        y: -5
        height: 24
        text: qsTr("alfa max")
        anchors.left: parent.left
        anchors.topMargin: 71
        anchors.top: parent.top
        anchors.leftMargin: 27
        font.pixelSize: 12
        anchors.rightMargin: 107
        anchors.right: parent.right
    }

    Text {
        id: text3
        x: 2
        y: -9
        height: 24
        text: qsTr("Text")
        anchors.left: parent.left
        anchors.topMargin: 113
        anchors.top: parent.top
        anchors.leftMargin: 27
        font.pixelSize: 12
        anchors.rightMargin: 107
        anchors.right: parent.right
    }

    Rectangle {
        id: rectangle1
        x: 101
        y: 32
        width: 63
        height: 24
        color: "#e8e9ee"

        Text {
            id: text6
            objectName: "fitnessText1"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.fill: parent
            font.pixelSize: 12
        }
    }

    Rectangle {
        id: rectangle2
        x: 100
        y: 71
        width: 63
        height: 24
        color: "#e8e9ee"

        Text {
            id: text5
            objectName: "fitnessText2"
            x: 20
            y: 0
            height: 24
            verticalAlignment: Text.AlignVCenter
            anchors.verticalCenter: parent.verticalCenter
            wrapMode: Text.NoWrap
            font.pixelSize: 12
        }
    }

    Rectangle {

        id: rectangle3
        x: 100
        y: 113
        width: 63
        height: 24
        color: "#e8e9ee"


        Text {
            id: text4
            objectName: "fitnessText3"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.fill: parent
            font.pixelSize: 12
        }
    }
}
