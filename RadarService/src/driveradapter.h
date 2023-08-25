#pragma once

#include <QProcess>
#include <QJsonDocument>
#include <QObject>

// Класс, отвечающий за взаимодействие с драйвером Радара. Читает данные из стандартного потока, преобразует их в формат JSON
class DriverAdapter : public QObject
{
    Q_OBJECT
public:
    explicit DriverAdapter(QObject *parent = nullptr);
    ~DriverAdapter();

public slots:
    void start();

private:
    QProcess * _process;

private slots:
    void readStandardOutput();

signals:
    void dataRecieved(const QJsonDocument &);
};
