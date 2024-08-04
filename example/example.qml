import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material
import GraphLibraryTest

Window {
    width: 640
    height: 400
    visible: true
    title: qsTr("Example Project")

    QCustomGraph {
        id: graph
        anchors.top: parent.top
        anchors.margins: 20
        width: parent.width
        height: 100

        function newSample(i) {
            return (Math.sin(i / 200.0 * Math.PI * 2) + 1) * 0.4 + Math.random() * 0.05;
        }

        Component.onCompleted: {
            for (var i=0; i<graph.offset; ++i)
                appendSample(newSample(i));
        }

        property int offset: 200
    }

    FrameAnimation {
        running: true
        onTriggered: {
            graph.removeFirstSample();
            graph.appendSample(graph.newSample(++graph.offset));
        }
    }
}
