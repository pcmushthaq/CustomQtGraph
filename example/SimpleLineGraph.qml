import QtQuick
import QCustomGraph

QCustomGraph {
    id: graph
    anchors.top: parent.top
    anchors.margins: 20
    anchors.horizontalCenter: parent.horizontalCenter
    width: parent.width - 20
    height: parent.height

    serieses: [
        LineGraphSeries {
            id: lineSeries
            color: "green"
            points: [
                XYPoint {
                    x: 0
                    y: 10
                },
                XYPoint {
                    x: 10
                    y: 5
                },
                XYPoint {
                    x: 20
                    y: 20
                },
                XYPoint {
                    x: 30
                    y: 15
                },
                XYPoint {
                    x: 40
                    y: 30
                },
                XYPoint {
                    x: 50
                    y: 25
                },
                XYPoint {
                    x: 60
                    y: 40
                }
            ]

            axisX: ValueAxis {
                min: 0
                max: 60
            }

            axisY: ValueAxis {
                min: 0
                max: 40
            }
        }
    ]
}
