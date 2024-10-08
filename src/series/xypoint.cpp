#include "xypoint.h"

XYPoint::XYPoint(QObject *parent)
    : QObject{parent}
{}

XYPoint::XYPoint(qreal x, qreal y,QObject *parent) :
    QObject{parent},m_x{x},m_y{y}
{

}

double XYPoint::x() const
{
    return m_x;
}

void XYPoint::setX(double newX)
{
    if (qFuzzyCompare(m_x, newX))
        return;
    m_x = newX;
    emit xChanged();
}

double XYPoint::y() const
{
    return m_y;
}

void XYPoint::setY(double newY)
{
    if (qFuzzyCompare(m_y, newY))
        return;
    m_y = newY;
    emit yChanged();
}
