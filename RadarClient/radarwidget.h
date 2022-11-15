#pragma once
#include "radarobject.h"

#include <QWidget>
#include <QMap>

// Класс-виджет, отображающий радар и объекты, которые обнаружены на серверной стороне с использованием приложения RadarDriver
class RadarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RadarWidget(QWidget *parent = nullptr);
    ~RadarWidget();

protected:
    void paintEvent(QPaintEvent *event);

public slots:
    void updateObjects(const RadarObject & object);

private:
    QMap<QString, RadarObject> _objects;
};
