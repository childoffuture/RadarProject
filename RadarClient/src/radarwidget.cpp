#include "radarwidget.h"

#include <QPainter>
#include <QDebug>

RadarWidget::RadarWidget(QWidget *parent) : QWidget(parent)
{}

RadarWidget::~RadarWidget()
{}

void RadarWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPoint center((pos().x() + width()) / 2, (pos().y() + height()) / 2);

    QPainter p;
    p.begin(this);
    p.setPen(Qt::darkGreen);
    p.drawLine(QLine(center.x(), 0, center.x(), height()));
    p.drawLine(QLine(0, center.y(), width(), center.y()));

    int circleCount = qMin(width(), height()) / 20;
    for(int i = 0; i < circleCount; ++i)
    {
        p.drawEllipse(center, i * 20, i * 20);
    }

    foreach(RadarObject object, _objects.values())
    {
        p.setBrush(object.color());
        p.setPen(object.color());

        QPointF lastPos;
        foreach(QPointF pos, object.posList())
        {
            QPointF newPos = center + QPointF(pos.x() * width() / 2.0, pos.y() * height() / 2.0);
            p.drawEllipse(newPos, 10, 10);
            if (!lastPos.isNull())
            {
                p.drawLine(lastPos, newPos);
            }
            lastPos = newPos;
        }

        p.setPen(Qt::black);
        p.drawText(lastPos, object.key());
    }

    p.end();
}

void RadarWidget::updateObjects(const RadarObject &object)
{
    if(object.status() == QString("lost"))
    {
        _objects.remove(object.key());
    }
    else if (object.status() == QString("leading"))
    {
        _objects[object.key()].addPos(object.lastPos());
    }
    else if (object.status() == QString("found"))
    {
        _objects.insert(object.key(), object);
    }

    update();
}
