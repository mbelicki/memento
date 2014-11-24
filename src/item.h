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

#ifndef ITEM_H
#define ITEM_H

#include "common.h"

#include <QString>
#include <QDateTime>

class Item
{
public:
    Item(entityid_t id, const QString &name, bool done)
        : _id(id)
        , _name(name)
        , _done(done)
    {}

    Item(const Item &item)
        : _id(item._id)
        , _name(item._name)
        , _done(item._done)
    {}

    inline entityid_t id() const { return _id; }
    inline const QString &name() const { return _name; }
    inline bool isDone() const { return _done; }
    inline void setDone(bool value) { _done = value; }

private:
    const entityid_t _id;
    const QString _name;
    bool _done;
};

#endif // ITEM_H
