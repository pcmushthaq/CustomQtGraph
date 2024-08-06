#ifndef LINEGRAPHSERIES_H
#define LINEGRAPHSERIES_H

#include <BaseGraphSeries.h>
#include <QQmlEngine>
#include <XYPoint.h>

class LineGraphSeries : public BaseGraphSeries

{
    Q_OBJECT
    Q_PROPERTY(qreal width READ width WRITE setWidth NOTIFY widthChanged FINAL)
    Q_PROPERTY(QQmlListProperty<XYPoint> points READ points FINAL)


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
signals:
    void widthChanged();
private:
    qreal m_width;
    QList<XYPoint*> m_points;
    QColor m_Color;
};

#endif // LINEGRAPHSERIES_H
