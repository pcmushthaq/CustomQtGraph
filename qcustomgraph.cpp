#include "linenode.h"
#include "qcustomgraph.h"
#include <iostream>
#include <QPainter>
#include <AreaGraphSeries.h>
#include <AreaNode.h>

QQmlListProperty<BaseGraphSeries> QCustomGraph::serieses()
{
    return QQmlListProperty<BaseGraphSeries>(this, nullptr, &QCustomGraph::append_series, nullptr,
                                             nullptr, nullptr, nullptr, nullptr);
}

QCustomGraph::QCustomGraph(QQuickItem *parent)
    : QQuickItem(parent)
{
    setFlag(ItemHasContents, true);
    m_samplesChanged=true;
}



QCustomGraph::~QCustomGraph() {}

class GraphNode : public QSGNode
{
public:
    std::vector <QSGNode *> lines;
};

QSGNode *QCustomGraph::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    GraphNode *n= static_cast<GraphNode *>(oldNode);

    QRectF rect = boundingRect();

    if (rect.isEmpty()) {
        delete n;
        return nullptr;
    }

    if (!n) {
        n = new GraphNode();

        for( const auto &ser:m_series){
            if(ser->graphType() == BaseGraphSeries::GraphType::LineGraph){
                auto lineSer=static_cast<LineGraphSeries*> (ser);
                auto node= new LineNode(10, 2, lineSer->color());
                n->lines.push_back(node);
                n->appendChildNode(node);
            }
            else if(ser->graphType() == BaseGraphSeries::GraphType::AreaGraph){

                auto areaSer=static_cast<LineGraphSeries*> (ser);
                auto node= new LineNode(10, 2, areaSer->color());
                n->lines.push_back(node);
                n->appendChildNode(node);
            }

        }


    }

    if (m_geometryChanged || m_samplesChanged) {
        for( int i=0;i<m_series.size();i++){
            if(m_series[i]->graphType() ==  BaseGraphSeries::GraphType::LineGraph) {
                /// Handle line graph
                auto lineSer=static_cast<LineGraphSeries*> (m_series[i]);
                auto lineNode=static_cast<LineNode *>(n->lines[i]);
                lineNode->updateGeometry(rect, lineSer->dataPoint(), 250);
            }
            else if(m_series[i]->graphType() ==  BaseGraphSeries::GraphType::AreaGraph) {
                /// Handle area graph
                auto areaSer=static_cast<AreaGraphSeries*> (m_series[i]);
                auto areaNode=static_cast<AreaNode *>(n->lines[i]);
                areaNode->updateGeometry(rect, areaSer->dataPoints(), 250);
            }
        }
        // for( const auto &lin: n->line){
        //         n->line.updateGeometry(rect, lin->dataPoint(),250);
        // }


    }

    m_geometryChanged = false;
    m_samplesChanged = false;

    return n;
}

void QCustomGraph::geometryChange(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    m_geometryChanged = true;
    update();
    QQuickItem::geometryChange(newGeometry, oldGeometry);
}

void QCustomGraph::appendSample(qreal value)
{
    m_samples << value;
    m_samplesChanged = true;
    update();
}

void QCustomGraph::removeFirstSample()
{
    m_samples.removeFirst();
    m_samplesChanged = true;
    update();
}

void QCustomGraph::append_series(QQmlListProperty<BaseGraphSeries> *list, BaseGraphSeries *ser)
{
    std::cout<<"Adding series"<<std::endl;
    QCustomGraph *chart = qobject_cast<QCustomGraph *>(list->object);
    if (chart) {
        // ser->setParentItem(chart);
        chart->m_series.append(ser);
        chart->m_samplesChanged=true;
    }
}
