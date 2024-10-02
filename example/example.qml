import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material

Window {
    width: Screen.width * 0.75
    height: 400
    visible: true
    title: qsTr("Example Project")

    Component {
        id: simpleLineGraph
        SimpleLineGraph {}
    }

    Component {
        id: liveLineGraph
        LiveLineGraph {}
    }

    Component {
        id: liveQtCharts
        LiveQtChartsLine {}
    }

    Button {
        anchors.top: parent.top
        anchors.left: parent.left
        text: "Back"
        visible: viewLoader.sourceComponent !== null
        onClicked: {
            viewLoader.sourceComponent = null
        }
    }

    Column {
        visible: viewLoader.sourceComponent === null
        anchors.centerIn: parent

        Button {
            text: "Simple LineGraph"
            onClicked: {
                viewLoader.sourceComponent = simpleLineGraph
            }
        }

        Button {
            text: "Live LineGraph"
            onClicked: {
                viewLoader.sourceComponent = liveLineGraph
            }
        }

        Button {
            text: "Live QtCharts"
            onClicked: {
                viewLoader.sourceComponent = liveQtCharts
            }
        }
    }

    Loader {
        id: viewLoader
        anchors.fill: parent
    }
}
