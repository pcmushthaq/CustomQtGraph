This is a library which can be used to plot line graphs in QtQuick. A QML component is created in the library.

The API is similar to the QtCharts API. This is intended to be used for high performance applications. This uses SceneGraph APIs for plotting the graphs.

This is hardware accelarated.

Support for AreaChart is under development.

## Example Line Graph

To create a simple line graph, create an instance of QCustomGraph and add a LineGraphSeries element inside

```
import QCustomGraph

QCustomGraph {
        id: graph
        anchors.fill: parent

        serieses:[
            LineGraphSeries{
                id: lineSeries
                points: [
                    XYPoint{ x: 0; y: 0.1},
                    XYPoint{ x: 1 ;y: 0.2},
                    XYPoint{ x: 2 ;y: 0.3}
                ]
            }
        ]
    }
```
