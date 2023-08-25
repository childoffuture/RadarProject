#pragma once
#include "radarobject.h"

#include <QObject>
#include <QTcpSocket>
#include <QJsonDocument>

// Класс, отвечающий за получение данных от сервера и передающий их для отображения в виде объекта RadarObject
class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);

public slots:
    void start();
    void stop();

private:
    QTcpSocket * _socket;
    QString _buffer;

    void parseData(const QString & data);

private slots:
    void readServer();
    void onDisconnected();


signals:
    void message(const QString &);
    void dataRecieved(const RadarObject &);
};
