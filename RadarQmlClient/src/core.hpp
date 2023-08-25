#pragma once
#include "radarobject.hpp"

#include <QObject>
#include <QMap>

class ListModel;

class Core : public QObject
{
    Q_OBJECT
public:
    explicit Core(QObject *parent = nullptr);
    ~Core();

    ListModel * model() const;

private:
    ListModel * _model;
    QMap<QString, RadarObject> _objects;
    const int _objectCount;

private slots:
    void updateModel(const RadarObject &object);
};

