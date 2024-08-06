import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material
import GraphLibraryTest

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

        function newSample(i) {
            return (Math.sin(i / 200.0 * Math.PI * 2) + 1) * 0.4 + Math.random() * 0.05;
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
            //     id: asd
            //     points: [XYPoint{x:0;y:0.1 },
            //         XYPoint{ x: 1 ;y:0.2},
            //         XYPoint{ x: 2 ;y:0.3}]
            // },
            // LineGraphSeries{
            //     id: asd2
            //     points: [XYPoint{x:0;y:0.8 },
            //         XYPoint{ x: 1 ;y:0.6},
            //         XYPoint{ x: 2 ;y:0.8}]
            // },

            AreaGraphSeries{
                color: "red"
                upperSeries: LineGraphSeries{
                    id: asd3
                    points: [
                        XYPoint{x:0;y:0.1 },
                        XYPoint{ x: 1 ;y:0.5},
                        XYPoint{ x: 2 ;y:0.3},
                         XYPoint{ x: 3 ;y:0.4}

                    ]
                }

                lowerSeries: LineGraphSeries{
                    id: asd2
                    points: [XYPoint{x:0;y:0.8 },
                        XYPoint{ x: 1 ;y:0.6},
                        XYPoint{ x: 2 ;y:0.8}
                    ]
                }
            }
        ]
    }
}
