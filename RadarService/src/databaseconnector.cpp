#include "databaseconnector.h"

#include <QJsonObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QUuid>
#include <QDateTime>
#include <QTimer>
#include <QDebug>

DatabaseConnector::DatabaseConnector(QObject *parent) : QObject(parent)
    , _connectionName(QUuid::createUuid().toString())
{   
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", _connectionName);
    db.setDatabaseName("database.sqlite");
    if(db.open())
    {
        qDebug() << "Database connection established";

        QSqlQuery query(db);
        query.prepare("CREATE TABLE IF NOT EXISTS objects (id text, state text, x float, y float, ts text);");
        if(!query.exec())
        {
            qDebug() << query.lastError().text();
        }

        QTimer * timer = new QTimer(this);
        timer->start(36000000);
        connect(timer, &QTimer::timeout, this, &DatabaseConnector::cleanDatabase);
    }
}

DatabaseConnector::~DatabaseConnector()
{}

void DatabaseConnector::updateStorage(const QJsonDocument &doc)
{
    if (doc.isObject())
    {
        QJsonObject mainObject = doc.object();        
        QJsonObject posObject = mainObject.value("pos").toObject();

        QSqlDatabase db = QSqlDatabase::database(_connectionName);
        if (db.isOpen())
        {
            QSqlQuery query(db);
            query.prepare("INSERT INTO objects (id, state, x, y, ts) VALUES (?, ?, ?, ?, ?);");
            query.addBindValue(mainObject.value("id").toString());
            query.addBindValue(mainObject.value("state").toString());
            query.addBindValue(posObject.value("x").toDouble());
            query.addBindValue(posObject.value("y").toDouble());
            query.addBindValue(mainObject.value("ts").toString());

            if(!query.exec())
            {
                qDebug() << query.lastError().text();
            }
        }
    }
}

void DatabaseConnector::getHistory()
{
    QSqlDatabase db = QSqlDatabase::database(_connectionName);
    if (db.isOpen())
    {
        QSqlQuery query(db);
        QString code = QString("SELECT * FROM objects ORDER BY id, ts;");
        if(query.exec(code))
        {
            QList<QJsonDocument> list;

            while(query.next())
            {
                QString id = query.record().value("id").toString();
                QString state = query.record().value("state").toString();
                QString ts = query.record().value("ts").toString();
                double x = query.record().value("x").toDouble();
                double y = query.record().value("y").toDouble();

                QJsonObject posObject;
                posObject.insert("x", x);
                posObject.insert("y", y);

                QJsonObject mainObject;
                mainObject.insert("id", id);
                mainObject.insert("state", state);
                mainObject.insert("ts", ts);
                mainObject.insert("pos", posObject);

                QJsonDocument doc;
                doc.setObject(mainObject);

                list.push_back(doc);
            }

            emit historyPrepared(list);
        }
        else
        {
            qDebug() << query.lastError().text();
        }
    }
}

void DatabaseConnector::cleanDatabase()
{
    QSqlDatabase db = QSqlDatabase::database(_connectionName);
    if (db.isOpen())
    {
        QDate date = QDate::currentDate().addDays(-180);
        QSqlQuery query(db);
        QString code = QString("delete  from objects where ts < '%1%'").arg(date.toString("dd.MM.yyyy"));
        if(!query.exec(code))
        {
            qDebug() << query.lastError().text();
        }
    }
}
