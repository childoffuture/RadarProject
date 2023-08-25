#pragma once

#include <QObject>
#include <QJsonDocument>

// Класс, отвечающий за взаимодействие с БД.
// Сохраняет поступающие данные, может выдать список сохраненных записей, по таймеру очищает старые записи из БД
class DatabaseConnector : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseConnector(QObject *parent = nullptr);
    ~DatabaseConnector();

public slots:
    void updateStorage(const QJsonDocument & doc);
    void getHistory();

signals:
    void historyPrepared(const QList<QJsonDocument> &);

private slots:
    void cleanDatabase();

private:
    QString _connectionName;
};
