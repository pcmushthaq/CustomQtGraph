#include "linenode.h"
#include "qcustomgraph.h"

#include <QPainter>

QCustomGraph::QCustomGraph(QQuickItem *parent)
    : QQuickItem(parent)
{
    // By default, QQuickItem does not draw anything. If you subclass
    // QQuickItem to create a visual item, you will need to uncomment the
    // following line and re-implement updatePaintNode()

    setFlag(ItemHasContents, true);
    m_samplesChanged=true;
}



QCustomGraph::~QCustomGraph() {}

class GraphNode : public QSGNode
{
public:
    LineNode *line;
    LineNode *shadow;
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

        n->line = new LineNode(10, 10, QColor("steelblue"));
        n->shadow = new LineNode(20, 0.2f, QColor::fromRgbF(0.2, 0.2, 0.2, 0.4));

        n->appendChildNode(n->shadow);
        n->appendChildNode(n->line);
    }

    if (m_geometryChanged || m_samplesChanged) {
        n->line->updateGeometry(rect, m_samples,250);
        // We don't need to calculate the geometry twice, so just steal it from the other one...
        n->shadow->setGeometry(n->line->geometry());
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
