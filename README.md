This is a library which can be used to plot line graphs in QML/QtQuick. A QML component is created in the library.

The API is similar to the QtCharts API but the performance is much better than QtCharts [See](#performance-comparison-with-qtcharts). This is intended to be used for high performance applications. This uses SceneGraph APIs for plotting the graphs.

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


## Performance Comparison with QtCharts

QtCharts uses QPainter behind the scenes to draw the graph which uses software rendering. It can be quite ineffective. Although, LineSeries and ScatterSeries from QtCharts support OpenGL accelaration, it won't work if QML RHI backend is defined as something else, as it typically is by default in Qt 6. 

A live sine graph is created both using the QtCharts and the QCustomGraph library and QML profiler was used to analyse the performance differences.

The QCustomGraph has a 75% better performance compared to QtCharts. The mean time for adding a new point has reduced to 40 us from 160 us which is a huge improvement.
The examples are available as part of the example project.

![Alt text](images/CustomGraphsProfile.png?raw=true "QML Profiler statistics for custom qt graph")

![Alt text](images/QtChartsProfile.png?raw=true "QML Profiler statistics for Qt Charts")


