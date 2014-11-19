#include "listwrapper.h"

#include <QDebug>

int ListWrapper::rowCount(const QModelIndex &parent) const
{
    int result = 0;
    if (parent.isValid() == false) {
        result = _collection->count();
    }
    return result;
}

QHash<int, QByteArray> ListWrapper::roleNames() const
{
    QHash<int, QByteArray> result;
    result[NameRole] = "name";
    result[ColorRole] = "listColor";
    result[IdRole] = "listId";
    return result;
}

QVariant ListWrapper::data(const QModelIndex &index, int role) const
{
    QVariant result;

    if (index.row() < _collection->count())
    {
        const TaskList *list = _collection->at(index.row());
        switch (role) {
        case NameRole:
            result.setValue(list->name());
            break;
        case ColorRole:
            result.setValue(list->color());
            break;
        case IdRole:
            result.setValue((unsigned int)list->id());
            break;
        }
    }

    return result;
}

