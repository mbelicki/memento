/*
 * Copyright 2014 Mateusz Belicki
 *
 * free.software@belickim.net
 *
 * This file is part of Memento (Sailfish OS todo app).
 *
 * Memento is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * Memento is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Memento. If not, see <http://www.gnu.org/licenses/>.
 */

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
    result[ImportantRole] = "itemImportant";
    result[UrgentRole] = "itemUrgent";
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
        case ImportantRole:
            result.setValue(item->isImportant());
            break;
        case UrgentRole:
            result.setValue(item->isUrgent());
            break;
        }
    }

    return result;
}

static unsigned int createItemFlags(bool isUrgent, bool isImportant) {
    unsigned int result = ItemFlags::NONE;

    if (isUrgent)    result |= ItemFlags::URGENT;
    if (isImportant) result |= ItemFlags::IMPORTANT;

    return result;
}

void ItemsListModel::createItem
        (const QString &name, bool isUrgent, bool isImportant)
{
    int index = _list->size();
    beginInsertRows(QModelIndex(), index, index);
    unsigned int flags = createItemFlags(isUrgent, isImportant);
    _collection->createNewItemInList(_list->id(), name, flags);
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
