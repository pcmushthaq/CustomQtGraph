#ifndef QCUSTOMGRAPH_H
#define QCUSTOMGRAPH_H

#include <QQuickItem>

class QCustomGraph : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT
    Q_DISABLE_COPY(QCustomGraph)
public:
    explicit QCustomGraph(QQuickItem *parent = nullptr);
    ~QCustomGraph() override;

protected:
    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);
    void geometryChange(const QRectF &newGeometry, const QRectF &oldGeometry);

public slots:
    void appendSample(qreal value);

    void removeFirstSample();

private:
    QList<QPointF> m_points;
    QList<qreal> m_samples;
    bool m_samplesChanged=false;
    bool m_geometryChanged=false;
};

#endif // QCUSTOMGRAPH_H
