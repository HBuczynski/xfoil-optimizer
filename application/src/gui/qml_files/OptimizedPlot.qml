import QtQuick 2.0
import QtCharts 2.0

ChartView {
    objectName: "optimizedPlot"
    anchors.fill: parent
    antialiasing: true
    backgroundColor: "#CED1D2"
    legend.visible: false

    property double yMax: 1
    property double yMin: -1

    function setAxis(yMx, yMn)
    {
        Qt.yMax = yMx
        Qt.yMin = yMn
    }

    ValueAxis {
        id: axisX
        min: 0
        max: 1
    }

    ValueAxis {
         id: axisY
         min: yMin
         max: yMax
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

    function clear()
    {
        series.clear();
    }
}

