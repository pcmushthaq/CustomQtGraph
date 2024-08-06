#ifndef QCUSTOMGRAPH_H
#define QCUSTOMGRAPH_H

#include <LineGraphSeries.h>
#include <QQuickItem>

class QCustomGraph : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT
    Q_DISABLE_COPY(QCustomGraph)

    Q_PROPERTY(QQmlListProperty<BaseGraphSeries> serieses READ serieses FINAL)
public:

    QQmlListProperty<BaseGraphSeries> serieses();

    explicit QCustomGraph(QQuickItem *parent = nullptr);
    ~QCustomGraph() override;

protected:
    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);
    void geometryChange(const QRectF &newGeometry, const QRectF &oldGeometry);

public slots:
    void appendSample(qreal value);

    void removeFirstSample();

private:
    static void append_series(QQmlListProperty<BaseGraphSeries> *list, BaseGraphSeries *ser);
    QList<QPointF> m_points;
    QList<BaseGraphSeries *> m_series;
    QList<qreal> m_samples;
    bool m_samplesChanged=false;
    bool m_geometryChanged=false;
};

#endif // QCUSTOMGRAPH_H
