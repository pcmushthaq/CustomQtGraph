#ifndef AREANODE_H
#define AREANODE_H

#include <QSGGeometryNode>
#include <XYPoint.h>

class AreaNode : public QSGGeometryNode
{
public:
    AreaNode(float size, float spread,const QColor &color);

    void updateGeometry(const QRectF &bounds, const QList<XYPoint *> &upperSamples);

private:
    QSGGeometry m_geometry;

};
#endif // AREANODE_H
