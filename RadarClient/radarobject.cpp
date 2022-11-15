#include "radarobject.h"

RadarObject::RadarObject() : _color(generateColor())
{}

RadarObject::RadarObject(const QString & key, const QString & status, const QPointF & pos) : _key(key), _status(status), _color(generateColor())
{
    addPos(pos);
}

RadarObject::RadarObject(const RadarObject &other) : _key(other.key()), _status(other.status()), _posList(other.posList()), _color(other.color())
{}

RadarObject::~RadarObject()
{}

void RadarObject::setKey(const QString & key)
{
   _key = key;
}

QString RadarObject::key() const
{
    return _key;
}

void RadarObject::setStatus(const QString & status)
{
    _status = status;
}

QString RadarObject::status() const
{
    return _status;
}

void RadarObject::addPos(const QPointF &pos)
{
    _posList.push_back(pos);
}

QPointF RadarObject::lastPos() const
{
    return (_posList.empty()) ? QPointF() : _posList.last();
}

QList<QPointF> RadarObject::posList() const
{
    return _posList;
}

void RadarObject::setPosList(const QList<QPointF> &list)
{
    _posList = list;
}

QColor RadarObject::color() const
{
    return _color;
}

QColor RadarObject::generateColor() const
{
    srand(time(NULL));
    int r = (rand() % 255);
    int g = (rand() % 255);
    int b = (rand() % 255);
    return QColor(r, g, b);
}
