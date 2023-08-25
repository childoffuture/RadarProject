#pragma once

#include <QObject>
#include <QTcpServer>
#include <QJsonDocument>

// Сервер, отвечающий за передачу данных клиентским приложениям. Передает текущие данные для отображения. Может передать список всех записей в БД
class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(int port = 4221, QObject *parent = nullptr);
    ~Server();

public slots:
    void start();
    void sendCurrentData(const QJsonDocument & doc);
    void sendHistory(const QList<QJsonDocument> & history);

protected:
    void incomingConnection(qintptr handle);

private slots:
    void onDisconnected();
    void readClient();

private:
    QList<QTcpSocket *> _currentClients;
    int _port;

    void sendToClient(QTcpSocket * client, const QString & msg);
    void sendToClient(QTcpSocket * client, const QJsonObject & object);

signals:
    void getHistory();


};
