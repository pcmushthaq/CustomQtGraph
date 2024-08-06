#ifndef XYPOINT_H
#define XYPOINT_H

#include <QObject>
#include <QQmlEngine>

class XYPoint : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(double x READ x WRITE setX NOTIFY xChanged FINAL)
    Q_PROPERTY(double y READ y WRITE setY NOTIFY yChanged FINAL)
public:
    explicit XYPoint(QObject *parent = nullptr);

    double x() const;
    void setX(double newX);

    double y() const;
    void setY(double newY);

signals:
    void xChanged();
    void yChanged();

private:
    double m_x=0.0;
    double m_y=0.0;
};

#endif // XYPOINT_H
