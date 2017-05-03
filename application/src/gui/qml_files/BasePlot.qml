import QtQuick 2.0
import QtCharts 2.0

ChartView {
    objectName: "basePlot"
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
        id: lol1
        axisX: axisX
        axisY: axisY
//        XYPoint { x: 0; y: 0.0 }
//        XYPoint { x: 1.1; y: 3.2 }
//        XYPoint { x: 1.9; y: 2.4 }
//        XYPoint { x: 2.1; y: 2.1 }
//        XYPoint { x: 2.9; y: 2.6 }
//        XYPoint { x: 2.1; y: 1.3 }
//        XYPoint { x: 1.9; y: 1.1 }
    }

    Component.onCompleted: {
        for (var i = 0; i <= 100; i++) {
            lol1.append(i, (Math.random()-1));

        }
    }
}


