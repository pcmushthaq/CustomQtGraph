import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material
import QCustomGraph

Window {
    width: Screen.width * 0.75
    height: 400
    visible: true
    title: qsTr("Example Project")



    QCustomGraph {
        id: graph
        anchors.top: parent.top
        anchors.margins: 20
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width - 20
        height: parent.height

        Timer{
            interval: 5
            running: true
            repeat: true
            onTriggered: {
                graph.newSample()
            }
        }

        property int inumber : 0

        function newSample(i) {

            var value= (Math.sin(inumber / 200.0 * Math.PI * 2) + 1) * 0.4 + Math.random() * 0.05;
            inumber++;
            if (inumber === 200){
                inumber=0;
            }
            // lineSeries1.addPoint(inumber,value)
            areaUpperLineSeries.addPoint(inumber,value/2)
            areaLowerLineSeries.addPoint(inumber,0)
            if(areaUpperLineSeries.pointsCount >= 800){
                // lineSeries1.removeFirst()
                areaUpperLineSeries.removeFirst()
                areaLowerLineSeries.removeFirst()

            }
        }

        Component.onCompleted: {
            for (var i=0; i<graph.offset; ++i)
                appendSample(newSample(i));
            appendSample(0.1)
            appendSample(0.3)
            appendSample(0.2)

        }

        property int offset: 0

        serieses:[
            // LineGraphSeries{
            //     id: lineSeries1
            //     points: [
            //         XYPoint{x:0;y:0.1 },
            //         XYPoint{ x: 1 ;y:0.2},
            //         XYPoint{ x: 2 ;y:0.3}
            //     ]
            // },

            AreaGraphSeries{
                color: "red"
                upperSeries: LineGraphSeries{
                    id: areaUpperLineSeries
                    points: [
                        XYPoint{x:0;y:0.1 },
                        XYPoint{ x: 1 ;y:0.5},
                        XYPoint{ x: 2 ;y:0.3},
                         XYPoint{ x: 3 ;y:0.4}

                    ]
                }

                lowerSeries: LineGraphSeries{
                    id: areaLowerLineSeries
                    points: [XYPoint{x:0;y:0.8 },
                        XYPoint{ x: 1 ;y:0.6},
                        XYPoint{ x: 2 ;y:0.8}
                    ]
                }
            }
        ]
    }
}
