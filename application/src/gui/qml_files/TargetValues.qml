import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1

GroupBox {
    id: groupBox1
    x: 335
    width: 200
    height: 200
    anchors.right: parent.right
    anchors.rightMargin: 26
    anchors.top: parent.top
    anchors.topMargin: 7
    title: qsTr("TARGET VALUES")

    Label {
        id: label1
        width: 37
        height: 20
        text: qsTr("CL")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
        anchors.top: parent.top
        anchors.topMargin: 33
        anchors.left: parent.left
        anchors.leftMargin: 18
    }

    TextField {
        id: textField1
        x: 94
        y: 33
        width: 86
        height: 20
        placeholderText: qsTr("")
    }

    Label {
        id: label2
        x: 3
        y: -7
        width: 37
        height: 20
        text: qsTr("Alfa max")
        verticalAlignment: Text.AlignVCenter
        anchors.leftMargin: 18
        anchors.top: parent.top
        anchors.topMargin: 73
        anchors.left: parent.left
    }

    Label {
        id: label3
        x: -1
        y: -1
        width: 37
        height: 20
        text: qsTr("Label")
        verticalAlignment: Text.AlignVCenter
        anchors.leftMargin: 18
        anchors.top: parent.top
        anchors.topMargin: 117
        anchors.left: parent.left
    }

    TextField {
        id: textField2
        x: 94
        y: 73
        width: 86
        height: 20
        placeholderText: qsTr("")
    }

    TextField {
        id: textField3
        x: 94
        y: 117
        width: 86
        height: 20
        placeholderText: qsTr("")
    }
}
