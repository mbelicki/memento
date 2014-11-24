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

#ifndef LISTCOLLECTION_H
#define LISTCOLLECTION_H

#include "common.h"
#include "tasklist.h"
#include "ordering.h"

#include <QObject>
#include <QHash>
#include <QVariantList>
#include <QAbstractListModel>

class ListCollection : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QObject* activeList READ activeList NOTIFY activeListChanged)

    friend class DataBasePersistence;

public:
    ListCollection();
    ~ListCollection();

    Q_INVOKABLE const TaskList *createAndAddNewList
            ( const QString &name
            , const QColor &color
            );
    Q_INVOKABLE void createNewItemInList
            ( entityid_t listId
            , const QString &itemName
            );

    Q_INVOKABLE bool setActiveList(unsigned int /*entityid_t*/ id);
    Q_INVOKABLE QObject *createListModel(unsigned int id);

    Q_INVOKABLE QList<QObject *> getOrderedLists() const;
    inline QObject *activeList() const { return _activeList; }

    const TaskList *at(int index) const;
    const TaskList *byId(entityid_t id) const;
    int indexOf(entityid_t id) const { return _order.indexOf(id); }

    inline int size() const { return _lists.size(); }

    bool setChecked(entityid_t itemId, bool value);

signals:
    void activeListChanged();

protected:
    /* interface for persistence classes */
    bool insertList(entityid_t id, const QString &name, const QColor &color);
    bool insertItem(entityid_t id, const QString &name, bool done, entityid_t parentId);

    inline void setLastId(entityid_t id) { _nextId = id;}
    inline entityid_t lastId() const { return _nextId; }

private:
    QHash<entityid_t, TaskList *> _lists;
    QHash<entityid_t, Item *> _items;

    Ordering _order;
    entityid_t _nextId;
    TaskList *_activeList;

    entityid_t getNextId();
};

#endif // LISTCOLLECTION_H
