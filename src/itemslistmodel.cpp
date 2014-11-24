#include "itemslistmodel.h"

#include "item.h"

int ItemsListModel::rowCount(const QModelIndex &parent) const
{
    int result = 0;
    if (parent.isValid() == false) {
        result = _list->size();
    }
    return result;
}

QHash<int, QByteArray> ItemsListModel::roleNames() const
{
    QHash<int, QByteArray> result;
    result[NameRole] = "name";
    result[IdRole] = "itemId";
    result[DoneRole] = "itemDone";
    return result;
}

QVariant ItemsListModel::data(const QModelIndex &index, int role) const
{
    QVariant result;

    if (index.row() < _list->size())
    {
        const Item *item = _list->at(index.row());
        switch (role) {
        case NameRole:
            result.setValue(item->name());
            break;
        case IdRole:
            result.setValue((unsigned int)item->id());
            break;
        case DoneRole:
            result.setValue(item->isDone());
            break;
        }
    }

    return result;
}

void ItemsListModel::createItem(const QString &name)
{
    int index = _list->size();
    beginInsertRows(QModelIndex(), index, index);
    _collection->createNewItemInList(_list->id(), name);
    endInsertRows();

    emit sizeChanged();
}

void ItemsListModel::setChecked(int i, bool value)
{
    if (i < 0 || i >= _list->size()) return;

    entityid_t id = _list->at(i)->id();
    _collection->setChecked(id, value);

    QModelIndex index = createIndex(i, 0);
    emit dataChanged(index, index);

    _list->updateDoneCount();
    emit doneCountChanged();
}
