#pragma once

#include <QObject>

class DriverAdapter;
class DatabaseConnector;
class Server;

// Класс-ядро. Организует взаимодействие между модулями приложения
class Core : public QObject
{
    Q_OBJECT
public:
    explicit Core(QObject *parent = nullptr);
    ~Core();

    void init();

private:
    DriverAdapter * _adapter;
    DatabaseConnector * _connector;
    Server * _server;

};
