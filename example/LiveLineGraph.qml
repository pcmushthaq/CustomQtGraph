import QtQuick
import QCustomGraph

QCustomGraph {
    id: graph
    anchors.top: parent.top
    anchors.margins: 20
    anchors.horizontalCenter: parent.horizontalCenter
    width: parent.width - 20
    height: parent.height

    Timer {
        interval: 5
        running: true
        repeat: true
        onTriggered: {
            graph.newSample()
        }
    }

    property int inumber: 0
    property int maxCount: 1000

    function newSample(i) {

        var value = (Math.sin(inumber / 200.0 * Math.PI * 2) + 1) * 0.4
        inumber++
        if (inumber === graph.maxCount) {
            inumber = 0
        }
        lineSeries.addPoint(inumber, value * 100)
        if (lineSeries.pointsCount >= graph.maxCount) {
            lineSeries.clear()
        }
    }

    serieses: [
        LineGraphSeries {
            id: lineSeries
            color: "green"
            points: []

            axisX: ValueAxis {
                min: 0
                max: graph.maxCount
            }

            axisY: ValueAxis {
                min: 0
                max: 100
            }
        }
    ]
}
