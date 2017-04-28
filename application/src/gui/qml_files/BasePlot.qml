import QtQuick 2.0
import QtCharts 2.0

ChartView {
    //title: "Spline"
    anchors.fill: parent
    antialiasing: true
    backgroundColor: "#CED1D2"

    SplineSeries {
        XYPoint { x: 0; y: 0.0 }
        XYPoint { x: 1.1; y: 3.2 }
        XYPoint { x: 1.9; y: 2.4 }
        XYPoint { x: 2.1; y: 2.1 }
        XYPoint { x: 2.9; y: 2.6 }
        XYPoint { x: 2.1; y: 1.3 }
        XYPoint { x: 1.9; y: 1.1 }
    }
}


