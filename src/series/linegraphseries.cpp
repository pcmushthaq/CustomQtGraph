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

ValueAxis* LineGraphSeries::axisX() const
{
    return m_axisX;
}

void LineGraphSeries::setAxisX(ValueAxis* &newAxisX)
{
    if (m_axisX == newAxisX)
        return;
    m_axisX = newAxisX;
    emit axisXChanged();
}

ValueAxis *LineGraphSeries::axisY() const
{
    return m_axisY;
}

void LineGraphSeries::setAxisY(ValueAxis *&newAxisY)
{
    if (m_axisY == newAxisY)
        return;
    m_axisY = newAxisY;
    emit axisYChanged();
}

void LineGraphSeries::addPoint(qreal x, qreal y)
{
    auto point= new XYPoint(x,y);
    m_points.push_back(point);
    emit seriesChanged();
}

void LineGraphSeries::removeFirst()
{
    m_points.removeFirst();
    emit seriesChanged();
}

void LineGraphSeries::clear()
{
    m_points.clear();
    emit seriesChanged();
}

int LineGraphSeries::pointsCount() const
{
    return m_points.size();
}
