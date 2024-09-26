#include "valueaxis.h"

ValueAxis::ValueAxis(QObject *parent)
    : BaseAxis{parent}
{}

QColor ValueAxis::color() const
{
    return m_Color;
}

void ValueAxis::setColor(const QColor &newColor)
{
    if (m_Color == newColor)
        return;
    m_Color = newColor;
    emit colorChanged();
}

double ValueAxis::min() const
{
    return m_min;
}

void ValueAxis::setMin(double newMin)
{
    if (qFuzzyCompare(m_min, newMin))
        return;
    m_min = newMin;
    emit minChanged();
}

double ValueAxis::max() const
{
    return m_max;
}

void ValueAxis::setMax(double newMax)
{
    if (qFuzzyCompare(m_max, newMax))
        return;
    m_max = newMax;
    emit maxChanged();
}
