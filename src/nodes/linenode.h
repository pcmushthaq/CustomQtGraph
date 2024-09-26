#ifndef LINENODE_H
#define LINENODE_H

#include <QSGGeometryNode>
#include <ValueAxis.h>
#include <XYPoint.h>

class LineNode : public QSGGeometryNode
{
public:
    LineNode(float size, float spread, const QColor &color);

    void updateGeometry(const QRectF &bounds,
                        const QList<XYPoint *> &samples,
                        ValueAxis *xAxis,
                        ValueAxis *yAxis);

private:
    QSGGeometry m_geometry;

};

#endif // LINENODE_H
