#include "listmodel.hpp"

ListModel::ListModel(QObject *parent) : QAbstractListModel(parent)
{
}

ListModel::~ListModel()
{}

void ListModel::setModelData(const QList<RadarObject> &list)
{
    beginRemoveRows(QModelIndex(), 0, _data.size());
    _data.clear();
    endRemoveRows();

    beginInsertRows(QModelIndex(), 0, list.size() - 1);
    _data = list;
    endInsertRows();
}

int ListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _data.size();
}

QVariant ListModel::data(const QModelIndex &index, int role) const
{
    QVariant value;

    if (index.isValid())
    {
        RadarObject object = _data.at(index.row());
        switch (role)
        {
            case NAME:
                value = object.key();
                break;
            case X_POS:
                value = object.lastPos().x();
                break;
            case Y_POS:
                value = object.lastPos().y();
                break;
            case COLOR:
                value = object.color();
                break;
            default:
                break;
        }
    }

    return value;
}

QHash<int, QByteArray> ListModel::roleNames() const
{
    QHash<int, QByteArray> names = QAbstractListModel::roleNames();
    names.insert(NAME, "text_data");
    names.insert(X_POS, "x_pos");
    names.insert(Y_POS, "y_pos");
    names.insert(COLOR, "object_color");

    return names;
}
