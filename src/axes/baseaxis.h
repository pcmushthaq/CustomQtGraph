#ifndef BASEAXIS_H
#define BASEAXIS_H

#include <QObject>
#include <QColor>
#include <QQmlEngine>

class BaseAxis : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Base Type Do not create")

    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged FINAL)


public:
    explicit BaseAxis(QObject *parent = nullptr);

    virtual QColor color() const = 0;
    virtual void setColor(const QColor &newColor) = 0;

signals:
    void colorChanged();
};

#endif // BASEAXIS_H
