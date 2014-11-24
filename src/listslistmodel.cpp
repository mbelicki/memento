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

#include "listslistmodel.h"

#include <QDebug>

static void connectTaskList(ListsListModel *model, const TaskList *list) {
    bool result = true;
    result = result && QObject::connect
            ( list, SIGNAL(sizeChanged(entityid_t))
            , model, SLOT(itemChanged(entityid_t))
            );
    result = result && QObject::connect
            ( list, SIGNAL(doneCountChanged(entityid_t))
            , model, SLOT(itemChanged(entityid_t))
            );
    if (result == false) {
        qDebug() << "Singal/slot connection failed.";
    }
}

ListsListModel::ListsListModel(ListCollection *collection)
    : _collection(collection)
{
    for (int i = 0; i < _collection->size(); i++) {
        const TaskList* list = _collection->at(i);
        connectTaskList(this, list);
    }
}

int ListsListModel::rowCount(const QModelIndex &parent) const
{
    int result = 0;
    if (parent.isValid() == false) {
        result = _collection->size();
    }
    return result;
}

QHash<int, QByteArray> ListsListModel::roleNames() const
{
    QHash<int, QByteArray> result;
    result[NameRole] = "name";
    result[ColorRole] = "listColor";
    result[IdRole] = "listId";
    result[SizeRole] = "listSize";
    result[DoneCountRole] = "doneCount";
    return result;
}

QVariant ListsListModel::data(const QModelIndex &index, int role) const
{
    QVariant result;

    if (index.row() < _collection->size())
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
        case SizeRole:
            result.setValue(list->size());
            break;
        case DoneCountRole:
            result.setValue(list->doneCount());
            break;
        }
    }

    return result;
}

void ListsListModel::addTaskList(const QString &name, const QColor &color)
{
    int index = _collection->size();
    beginInsertRows(QModelIndex(), index, index);
    const TaskList *list = _collection->createAndAddNewList(name, color);
    connectTaskList(this, list);
    endInsertRows();
}

void ListsListModel::itemChanged(entityid_t id)
{
    const TaskList *list = _collection->byId(id);
    if (list != NULL) {
        QModelIndex index = createIndex(_collection->indexOf(id), 0);
        emit dataChanged(index, index);
    }
}
