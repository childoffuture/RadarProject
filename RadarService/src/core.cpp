#include "core.h"

#include "driveradapter.h"
#include "databaseconnector.h"
#include "server.h"

#include <QThread>
#include <QDebug>

Core::Core(QObject *parent) : QObject(parent)
    , _adapter(0)
    , _connector(0)
    , _server(0)
{}

Core::~Core()
{}

void Core::init()
{
    qDebug() << __func__ << ">>>";

    _adapter = new DriverAdapter();
    _connector = new DatabaseConnector();
    _server = new Server();

    QThread * adapterThread = new QThread(this);
    QThread * dbThread = new QThread(this);
    QThread * serverThread = new QThread(this);

    connect(adapterThread, &QThread::started, _adapter, &DriverAdapter::start);
    connect(serverThread, &QThread::started, _server, &Server::start);

    connect(adapterThread, &QThread::finished, _adapter, &DriverAdapter::deleteLater);
    connect(dbThread, &QThread::finished, _connector, &DatabaseConnector::deleteLater);
    connect(dbThread, &QThread::finished, _server, &Server::deleteLater);

    connect(_adapter, &DriverAdapter::dataRecieved, _connector, &DatabaseConnector::updateStorage);
    connect(_adapter, &DriverAdapter::dataRecieved, _server, &Server::sendCurrentData);

    connect(_server, &Server::getHistory, _connector, &DatabaseConnector::getHistory);
    connect(_connector, &DatabaseConnector::historyPrepared, _server, &Server::sendHistory);

    dbThread->start();
    adapterThread->start();
    serverThread->start();

    qDebug() << __func__ << "<<<";
}
