import QtQuick 2.0
import QtCharts 2.0

ChartView {
    objectName: "optimizedPlot"
    anchors.fill: parent
    antialiasing: true
    backgroundColor: "#CED1D2"
    legend.visible: false

    ValueAxis {
        id: axisX
        min: 0
        max: 10
        tickCount: 5
    }

    ValueAxis {
         id: axisY
         min: -5
         max: 15
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

