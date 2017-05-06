import QtQuick 2.0
import QtCharts 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.2

Dialog {
    objectName: "optimizerDialog"
    visible: false
    title: "Plot"
    width: 800
    height: 500

    contentItem: Rectangle {
            ChartView {
                objectName: "basePlot"
                anchors.fill: parent
                antialiasing: true
                backgroundColor: "#CED1D2"
                legend.visible: false

                ValueAxis {
                    id: axisX
                    min: 0
                    max: 1
                }

                ValueAxis {
                     id: axisY
                     min: 0
                     max: 1
                 }

                SplineSeries {
                    id: series
                    axisX: axisX
                    axisY: axisY

                }

                function addData(x, y)
                {
                    for (var i = 0; i <= x.length; i++) {
                        series.append(x[i], y[i]);
                    }
                }
            }
    }
}
