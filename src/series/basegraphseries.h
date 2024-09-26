#ifndef BASEGRAPHSERIES_H
#define BASEGRAPHSERIES_H

#include <QColor>
#include <QObject>
#include <QQmlEngine>




class BaseGraphSeries : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Abstract Type Do not create")


    Q_PROPERTY(GraphType graphType READ graphType CONSTANT FINAL)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged FINAL)


public:
    enum class GraphType{
        LineGraph,
        AreaGraph
    };
    Q_ENUM(GraphType)

    explicit BaseGraphSeries(QObject *parent = nullptr);

    virtual BaseGraphSeries::GraphType graphType() const = 0;

    virtual QColor color() const = 0;
    virtual void setColor(const QColor &newColor) = 0;
signals:
    void colorChanged();

    void seriesChanged();
};

#endif // BASEGRAPHSERIES_H
