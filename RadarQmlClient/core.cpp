#include "core.hpp"
#include "client.hpp"
#include "listmodel.hpp"

#include <QRandomGenerator>
#include <QThread>

Core::Core(QObject *parent) : QObject(parent)
  , _model(new ListModel(this))
  , _objectCount(100)
{
    Client * client = new Client();

    QThread * thread = new QThread(this);
    client->moveToThread(thread);

    connect(thread, &QThread::started, client, &Client::start);
    connect(client, &Client::dataRecieved, this, &Core::updateModel);

    thread->start();
}

Core::~Core()
{}

ListModel *Core::model() const
{
    return _model;
}

void Core::updateModel(const RadarObject &object)
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

    _model->setModelData(_objects.values());
}
