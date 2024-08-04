#ifndef LINENODE_H
#define LINENODE_H

#include <QSGGeometryNode>

class LineNode : public QSGGeometryNode
{
public:
    LineNode(float size, float spread, const QColor &color);

    void updateGeometry(const QRectF &bounds, const QList<qreal> &samples, size_t maxPointCount);


private:
    QSGGeometry m_geometry;

};

#endif // LINENODE_H
