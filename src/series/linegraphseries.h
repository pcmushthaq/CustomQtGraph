#ifndef LINEGRAPHSERIES_H
#define LINEGRAPHSERIES_H

#include <BaseGraphSeries.h>
#include <QQmlEngine>
#include <ValueAxis.h>
#include <XYPoint.h>

class LineGraphSeries : public BaseGraphSeries

{
    Q_OBJECT
    Q_PROPERTY(qreal width READ width WRITE setWidth NOTIFY widthChanged FINAL)
    Q_PROPERTY(QQmlListProperty<XYPoint> points READ points FINAL)
    Q_PROPERTY(ValueAxis* axisX READ axisX WRITE setAxisX NOTIFY axisXChanged FINAL)
    Q_PROPERTY(int pointsCount READ pointsCount CONSTANT FINAL)

    QML_NAMED_ELEMENT(LineGraphSeries)

public:
   explicit LineGraphSeries(QObject *parent = nullptr);
    BaseGraphSeries::GraphType graphType() const override;

   QQmlListProperty<XYPoint> points();

    QList<XYPoint *> dataPoint();

    qreal width() const;
    void setWidth(qreal newWidth);

    QColor color() const override;
    void setColor(const QColor &newColor) override;
    ValueAxis* axisX() const;
    void setAxisX( ValueAxis* &newAxisX);

    int pointsCount() const;

public slots:
    void addPoint(qreal x,qreal y);
    void removeFirst();


signals:
    void widthChanged();
    void axisXChanged();

private:
    qreal m_width;
    QList<XYPoint*> m_points;
    QColor m_Color;
    ValueAxis* m_axisX;
    int m_pointsCount;
};

#endif // LINEGRAPHSERIES_H
