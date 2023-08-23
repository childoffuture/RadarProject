#include "client.hpp"
#include "radarobject.hpp"

#include <QHostAddress>
#include <QJsonObject>
#include <QPointF>
#include <QDebug>

Client::Client(QObject *parent) : QObject(parent)
    , _socket(new QTcpSocket(this))
{
    connect(_socket, &QTcpSocket::readyRead, this, &Client::readServer);
    connect(_socket, &QTcpSocket::disconnected, this, &Client::onDisconnected);
}

void Client::start()
{
    _socket->connectToHost(QHostAddress::LocalHost, 4221);
}

void Client::stop()
{
    _socket->disconnectFromHost();
}

void Client::parseData(const QString & data)
{
    QString rawData = data;
    QStringList list = rawData.replace(QString("}\n{"), QString("}##{")).split("##");

    foreach(QString msg, list)
    {
        QString data;
        if (msg == list.first() && !_buffer.isEmpty())
        {
            data.push_back(_buffer);
            data.push_back(msg);
        }
        else if (msg == list.last() && !msg.endsWith("}"))
        {
            _buffer = msg;
        }
        else
        {
            data = msg;
        }

        if (!data.isEmpty())
        {
            QJsonDocument document = QJsonDocument::fromJson(msg.toLatin1());

            if (document.isObject())
            {
                QJsonObject mainObject = document.object();
                QJsonValue value = mainObject.value("message");
                if (value == QJsonValue::Undefined)
                {
                    QJsonObject posObject = mainObject.value("pos").toObject();

                    QString key = mainObject.value("id").toString();
                    QString status = mainObject.value("state").toString();
                    double x = posObject.value("x").toDouble();
                    double y = posObject.value("y").toDouble();
                    QPointF pos(x,y);

                    RadarObject object(key, status, pos);

                    emit dataRecieved(object);
                }
                else
                {
                    emit message(value.toString());
                }
            }
        }
    }
}

void Client::readServer()
{
    if (_socket->waitForConnected(500))
    {
        _socket->waitForReadyRead(500);
        parseData(_socket->readAll());
    }
}

void Client::onDisconnected()
{
    _socket->deleteLater();
}
