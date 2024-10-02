import QtQuick
import QtCharts

ChartView {
    id: graph
    anchors.top: parent.top
    anchors.margins: 20
    anchors.horizontalCenter: parent.horizontalCenter
    width: parent.width - 20
    height: parent.height
    antialiasing: true

    ValueAxis {
        id: xAxis
        min: 0
        max: maxCount
    }

    ValueAxis {
        id: yAxis
        min: 0
        max: 100
    }

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
        lineSeries.append(inumber, value * 100)
        if (lineSeries.count >= graph.maxCount) {
            lineSeries.clear()
        }
    }

    LineSeries {
        id: lineSeries
        name: "LineSeries"
        color: "green"
        axisX: xAxis
        axisY: yAxis
    }
}
