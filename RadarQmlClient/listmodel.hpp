#pragma once
#include "radarobject.hpp"

#include <QAbstractListModel>

class ListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ListModel(QObject *parent = nullptr);
    ~ListModel();

    void setModelData(const QList<RadarObject> & list);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    QHash<int, QByteArray> roleNames() const;

private:
    enum ObjectProperty
    {
        NAME = Qt::UserRole + 1,
        X_POS,
        Y_POS,
        COLOR
    };

    QList<RadarObject> _data;

};
