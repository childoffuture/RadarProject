#include "radardriver.h"

#include <QDateTime>
#include <QUuid>
#include <QJsonObject>
#include <QJsonDocument>

#include "iostream"

using namespace std;

RadarDriver::RadarDriver(int objectCount, int frequency, QObject *parent) : QObject(parent)
    , _timer(new QTimer(this))
    , _objectCount(objectCount)
    , _interval((frequency != 0) ? 1000 / frequency : 1000)
{
    connect(_timer, &QTimer::timeout, this, &RadarDriver::updateObjectData);
}

void RadarDriver::start()
{
    srand(time(NULL));
    _timer->start(_interval);
}

void RadarDriver::newObject()
{
    if(_objectKeys.count() < _objectCount)
    {
        QString id = QUuid::createUuid().toString().remove('{').leftRef(5).toString();
        _objectKeys.push_back(id);
        printObjectData("found", id);
    }
}

void RadarDriver::updateObject()
{
    if(!_objectKeys.isEmpty())
    {
        int pos = (rand() % (_objectKeys.size()));
        QString id = _objectKeys.at(pos);
        printObjectData("leading", id);
    }
}

void RadarDriver::deleteObject()
{
    if(!_objectKeys.isEmpty())
    {
        int pos = (rand() % (_objectKeys.size()));
        QString id = _objectKeys.at(pos);
        _objectKeys.removeOne(id);
        printObjectData("lost", id);
    }
}

void RadarDriver::printObjectData(const QString &type, const QString &id)
{
    double x =  (rand() / (double)RAND_MAX) * 2 - 1;
    double y =  (rand() / (double)RAND_MAX) * 2 - 1;
    QString date = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss.zzz");

    QJsonObject posObject;
    posObject.insert("x", x);
    posObject.insert("y", y);

    QJsonObject mainObject;
    mainObject.insert("id", id);
    mainObject.insert("state", type);
    mainObject.insert("ts", date);
    mainObject.insert("pos", posObject);

    QJsonDocument doc;
    doc.setObject(mainObject);

    cout << QString(doc.toJson()).toStdString() << endl;
}

void RadarDriver::updateObjectData()
{
    int actionType = (rand() % 3);

    switch(actionType)
    {
        case Found:
            newObject();
            break;
        case Leading:
            updateObject();
            break;
        case Lost:
            deleteObject();
            break;
        default:
            break;
    }
}
