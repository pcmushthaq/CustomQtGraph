This is a library which can be used to plot line graphs in QtQuick. A QML component is created in the library.

The API is similar to the QtCharts API. This is intended to be used for high performance applications. This uses SceneGraph APIs for plotting the graphs.

This is hardware accelarated.

Support for AreaChart is under development.

## Example Line Graph

To create a simple line graph, create an instance of QCustomGraph and add a LineGraphSeries element inside.

The xAxis and yAxis should be set to plot the graphs properly

![Alt text](images/lineGraph.png?raw=true "Simple Line Graph")

```
import QCustomGraph

QCustomGraph {
        id: graph
        anchors.fill: parent

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
```
