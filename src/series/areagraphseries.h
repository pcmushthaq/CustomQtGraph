#ifndef AREAGRAPHSERIES_H
#define AREAGRAPHSERIES_H

#include <LineGraphSeries.h>
#include <QObject>
#include <QQmlEngine>

class AreaGraphSeries : public BaseGraphSeries
{
    Q_OBJECT
    QML_NAMED_ELEMENT(AreaGraphSeries)
    Q_PROPERTY(LineGraphSeries *upperSeries READ upperSeries WRITE setUpperSeries NOTIFY upperSeriesChanged FINAL)
    Q_PROPERTY(LineGraphSeries *lowerSeries READ lowerSeries WRITE setLowerSeries NOTIFY lowerSeriesChanged FINAL)


public:
    explicit AreaGraphSeries(QObject *parent = nullptr);
    BaseGraphSeries::GraphType graphType() const override;

    QList<XYPoint*> dataPoints();

    LineGraphSeries *upperSeries() const;
    void setUpperSeries(LineGraphSeries *newUpperSeries);

    LineGraphSeries *lowerSeries() const;
    void setLowerSeries(LineGraphSeries *newLowerSeries);

     QColor color() const override;
     void setColor(const QColor &newColor) override;

signals:
    void upperSeriesChanged();
    void lowerSeriesChanged();

private:
    LineGraphSeries *m_upperSeries = nullptr;
    LineGraphSeries *m_lowerSeries = nullptr;
    QColor m_Color;
};

#endif // AREAGRAPHSERIES_H
