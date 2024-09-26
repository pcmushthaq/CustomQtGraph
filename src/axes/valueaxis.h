#ifndef VALUEAXIS_H
#define VALUEAXIS_H

#include <QQmlEngine>
#include <QColor>
#include "baseaxis.h"

class ValueAxis : public BaseAxis
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(double min READ min WRITE setMin NOTIFY minChanged FINAL)
    Q_PROPERTY(double max READ max WRITE setMax NOTIFY maxChanged FINAL)

public:
    explicit ValueAxis(QObject *parent = nullptr);
    QColor color() const override;
    void setColor(const QColor &newColor) override;

    double min() const;
    void setMin(double newMin);

    double max() const;
    void setMax(double newMax);

signals:
    void minChanged();

    void maxChanged();

private:
    QColor m_Color;
    double m_min;
    double m_max;
};

#endif // VALUEAXIS_H
