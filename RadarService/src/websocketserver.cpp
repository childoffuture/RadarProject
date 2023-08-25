#include "websocketserver.h"

#include <QJsonDocument>
#include <QWebSocket>

WebSocketServer::WebSocketServer(QObject *parent) : QObject(parent)
    , _webSocketServer(0)
{}

WebSocketServer::~WebSocketServer()
{}

void WebSocketServer::start()
{
    _webSocketServer = new QWebSocketServer(QString("RadarWebSocketServer"), QWebSocketServer::NonSecureMode, this);
    _webSocketServer->listen(QHostAddress::Any, 1234);

    connect(_webSocketServer, &QWebSocketServer::newConnection, this, &WebSocketServer::onNewConnection);


    qDebug() << "WebSocketServer started";
}

void WebSocketServer::sendCurrentData(const QJsonDocument &doc)
{
    if (!_clients.isEmpty())
    {
        qDebug() << "WebSocketServer" << __func__ << QString(doc.toJson());
        foreach (QWebSocket * client, _clients)
        {
            client->sendTextMessage(doc.toJson());
        }
    }
}

void WebSocketServer::onNewConnection()
{
    qDebug() << __func__ ;

    QWebSocket * currentSocket = _webSocketServer->nextPendingConnection();
    _clients.push_back(currentSocket);

    connect(currentSocket, &QWebSocket::disconnected, this, &WebSocketServer::onClientDisconnected);

    currentSocket->sendTextMessage("Hello!");
}

void WebSocketServer::onClientDisconnected()
{
    QWebSocket * client = dynamic_cast<QWebSocket*>(sender());
    _clients.removeOne(client);
}
