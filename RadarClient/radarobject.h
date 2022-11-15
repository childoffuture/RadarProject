#pragma once

#include <QString>
#include <QPointF>
#include <QColor>
#include <QMetaType>

// Класс, использующийся для хранения данных об объекте в удобно для использования виде
class RadarObject
{
public:
    RadarObject();
    RadarObject(const QString & key, const QString & status, const QPointF & pos);
    RadarObject(const RadarObject & other);
    ~RadarObject();

    void setKey(const QString & key);
    QString key() const;

    void setStatus(const QString & status);
    QString status() const;

    void addPos(const QPointF & pos);
    QPointF lastPos() const;

    void setPosList(const QList<QPointF> & list);
    QList<QPointF> posList() const;


    QColor color() const;

private:
    QString _key;
    QString _status;
    QList<QPointF> _posList;
    QColor _color;

    QColor generateColor() const;
};

Q_DECLARE_METATYPE(RadarObject)
