import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Controls 1.4


ProgressBar {
    id: progressBar
    objectName: "busyIndicator"
    height: 40
    anchors.top: frameOptimizeChart.bottom
    anchors.topMargin: 6
    anchors.left: parent.left
    anchors.leftMargin: 618
    anchors.right: parent.right
    anchors.rightMargin: 32
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 0
    value: 0

}
