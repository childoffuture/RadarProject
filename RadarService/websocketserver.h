#pragma once
#include <QObject>
#include <QWebSocketServer>

class WebSocketServer : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketServer(QObject *parent = nullptr);
    ~WebSocketServer();

public slots:
    void start();
    void sendCurrentData(const QJsonDocument & doc);

private slots:
    void onNewConnection();
    void onClientDisconnected();

private:
   QWebSocketServer * _webSocketServer;
   QList<QWebSocket *> _clients;
};
