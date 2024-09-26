#include "areagraphseries.h"

AreaGraphSeries::AreaGraphSeries(QObject *parent)
    : BaseGraphSeries{parent}, m_Color{QColor(Qt::black)}
{}

BaseGraphSeries::GraphType AreaGraphSeries::graphType() const
{
    return GraphType::AreaGraph;
}

QList<XYPoint*> AreaGraphSeries::dataPoints()
{
    QList<XYPoint*> output;
    int i=0,j=0;
    auto upperPoints=m_upperSeries->dataPoint();
    auto lowerPoints=m_lowerSeries->dataPoint();
    while(i<lowerPoints.size() && j< upperPoints.size()){
        output.push_back(lowerPoints[i]);
        output.push_back(upperPoints[j]);
        i++;
        j++;
    }
    /// This will be true when lower series is larger than upper serires
    /// In that case keep appending the last upper point and the remaining lower pointts
    while(i<lowerPoints.size()){
        output.push_back(lowerPoints[i]);
        output.push_back(upperPoints[j-1]);
        i++;
    }
    /// This will be true when upper series is larger than lower serires
    /// In that case keep appending the last lower point and the remaining upper pointts
    while(j<upperPoints.size()){
        output.push_back(lowerPoints[i-1]);
        output.push_back(upperPoints[j]);
        j++;
    }
    return output;
}

LineGraphSeries *AreaGraphSeries::upperSeries() const
{
    return m_upperSeries;
}

void AreaGraphSeries::setUpperSeries(LineGraphSeries *newUpperSeries)
{
    if (m_upperSeries == newUpperSeries)
        return;
    QObject::disconnect(upperSeriesConnection);
    m_upperSeries = newUpperSeries;
    upperSeriesConnection = QObject::connect(m_upperSeries, &BaseGraphSeries::seriesChanged,
                                             this, &AreaGraphSeries::onLineSeriesChanged);

    emit upperSeriesChanged();
}

LineGraphSeries *AreaGraphSeries::lowerSeries() const
{
    return m_lowerSeries;
}

void AreaGraphSeries::setLowerSeries(LineGraphSeries *newLowerSeries)
{
    if (m_lowerSeries == newLowerSeries)
        return;
    QObject::disconnect(lowerSeriesConnection);
    m_lowerSeries = newLowerSeries;
    lowerSeriesConnection = QObject::connect(m_lowerSeries, &BaseGraphSeries::seriesChanged,
                                             this, &AreaGraphSeries::onLineSeriesChanged);

    emit lowerSeriesChanged();
}

QColor AreaGraphSeries::color() const
{
    return m_Color;
}

void AreaGraphSeries::setColor(const QColor &newColor)
{
    if (m_Color == newColor)
        return;
    m_Color = newColor;
    emit colorChanged();
}

ValueAxis *AreaGraphSeries::axisX() const
{
    return m_axisX;
}

void AreaGraphSeries::setAxisX(ValueAxis *newAxisX)
{
    if (m_axisX == newAxisX)
        return;
    m_axisX = newAxisX;
    emit axisXChanged();
}

void AreaGraphSeries::onLineSeriesChanged()
{
  emit seriesChanged();
}
