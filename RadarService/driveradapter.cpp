#include "driveradapter.h"

#include <QTimer>
#include <QJsonObject>
#include <QDebug>

DriverAdapter::DriverAdapter(QObject *parent) : QObject(parent)
  , _process(new QProcess(this))
{
    _process->setReadChannel(QProcess::StandardOutput);
    connect(_process, &QProcess::readyReadStandardOutput, this, &DriverAdapter::readStandardOutput);
}

DriverAdapter::~DriverAdapter()
{
    _process->terminate();
}

void DriverAdapter::start()
{
    _process->start("./RadarDriver");
    qDebug() << "DriverAdapter started";
}

void DriverAdapter::readStandardOutput()
{
  QByteArray rawData = _process->readAll();
  QJsonDocument doc = QJsonDocument::fromJson(rawData);
  if (doc.isObject())
  {
        emit dataRecieved(doc);
  }
}
