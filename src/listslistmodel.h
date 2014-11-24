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


#ifndef LISTWRAPPER_H
#define LISTWRAPPER_H

#include "listcollection.h"

#include <QAbstractListModel>

class ListsListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    ListsListModel(ListCollection *collection);

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void addTaskList(const QString &name, const QColor &color);

private slots:
    void itemChanged(entityid_t id);

private:
    enum Roles
        { NameRole = Qt::UserRole + 1
        , ColorRole
        , IdRole
        , SizeRole
        , DoneCountRole
        };

    ListCollection *_collection;

};

#endif // LISTWRAPPER_H
