#include "linegraphseries.h"


LineGraphSeries::LineGraphSeries(QObject *parent)
    :BaseGraphSeries(parent), m_Color{QColor(Qt::black)}
{

}

BaseGraphSeries::GraphType LineGraphSeries::graphType() const
{
    return BaseGraphSeries::GraphType::LineGraph;
}

QQmlListProperty<XYPoint> LineGraphSeries::points()
{
    return QQmlListProperty<XYPoint>(this, &this->m_points);
}

QList<XYPoint *> LineGraphSeries::dataPoint()
{
    return m_points;
}


qreal LineGraphSeries::width() const
{
    return m_width;
}

void LineGraphSeries::setWidth(qreal newWidth)
{
    if (qFuzzyCompare(m_width, newWidth))
        return;
    m_width = newWidth;
    emit widthChanged();
}

QColor LineGraphSeries::color() const
{
return m_Color;
}

void LineGraphSeries::setColor(const QColor &newColor)
{
    if (m_Color == newColor)
        return;
    m_Color = newColor;
    emit colorChanged();
}
