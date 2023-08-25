#pragma once

#include <QObject>
#include <QTimer>

// Класс-имитатор радара. Драйвер генерирует случайным образом данные об обнаруженных целях и выводит их в формате JSON в стандартный поток вывода
class RadarDriver : public QObject
{
    Q_OBJECT
public:
    RadarDriver(int objectCount, int frequency, QObject * parent = 0);

    void start();

private:
    QTimer * _timer;
    int _objectCount;
    int _interval;

    QStringList _objectKeys;

    enum ActionType
    {
        Found,
        Leading,
        Lost
    };

    void newObject();
    void updateObject();
    void deleteObject();
    void printObjectData(const QString & type, const QString & id);

private slots:
    void updateObjectData();
};
