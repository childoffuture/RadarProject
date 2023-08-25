#include "server.h"

#include <QJsonObject>
#include <QTcpSocket>

#include <QtConcurrent/QtConcurrentRun>

Server::Server(int port, QObject *parent) : QTcpServer(parent)
    , _port(port)
{}

Server::~Server()
{}

void Server::start()
{
    listen(QHostAddress::Any, _port);
    qDebug() << "server is listening";
}

void Server::sendCurrentData(const QJsonDocument &doc)
{
    foreach(QTcpSocket * client, _currentClients)
    {
        //QFuture< void > future = QtConcurrent::run(this, &Server::sendToClient, client, doc.object);
        sendToClient(client, doc.object());
    }
}

void Server::sendHistory(const QList<QJsonDocument> & history)
{
    QJsonObject result;
    int i = 0;
    foreach(QJsonDocument record, history)
    {
        result.insert(QString::number(i), record.object());
        ++i;
    }

    //sendToClient(_currentClient, result);
}

void Server::incomingConnection(qintptr handle)
{
    QTcpSocket * client = new QTcpSocket(this);
    client->setSocketDescriptor(handle);
    _currentClients.push_back(client);

    connect(client, &QTcpSocket::disconnected, this, &Server::onDisconnected);
    connect(client, &QTcpSocket::readyRead, this, &Server::readClient);

    sendToClient(client, QString("connected"));
}

void Server::onDisconnected()
{
    QTcpSocket * client = dynamic_cast<QTcpSocket*>(sender());
    _currentClients.removeOne(client);
    client->deleteLater();
}

void Server::readClient()
{
    QTcpSocket * client = dynamic_cast<QTcpSocket*>(sender());
    QByteArray result = client->readAll();

    QJsonParseError parseError;
    QJsonDocument document = QJsonDocument::fromJson(result, &parseError);
    int errorCode = parseError.errorString().toInt();
    if (errorCode == QJsonParseError::NoError)
    {
        qDebug() << document.toJson();
        sendToClient(client, QString("message recieved"));
    }
    else
    {
        sendToClient(client, QString("error : %1").arg(errorCode));
    }
}

void Server::sendToClient(QTcpSocket *client, const QString & msg)
{
    QJsonObject object;
    object.insert("message", msg);
    sendToClient(client, object);
}

void Server::sendToClient(QTcpSocket *client, const QJsonObject &object)
{
    QJsonDocument document;
    document.setObject(object);

    qDebug() << document.toJson();

    QByteArray data = document.toJson();
    client->write(data);
    client->waitForBytesWritten(500);
}
