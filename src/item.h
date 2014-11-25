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

namespace ItemFlags {
    enum itemflags_t
        { NONE = 0
        , DONE = 1
        , IMPORTANT = 2
        , URGENT = 4
        };
}

class Item
{
public:
    Item(entityid_t id, const QString &name, unsigned int flags)
        : _id(id)
        , _name(name)
        , _flags(flags)
    {}

    Item(const Item &item)
        : _id(item._id)
        , _name(item._name)
        , _flags(item._flags)
    {}

    inline entityid_t id() const { return _id; }
    inline const QString &name() const { return _name; }
    inline bool isDone() const { return 0 != (_flags & ItemFlags::DONE); }
    inline bool isImportant() const { return 0 != (_flags & ItemFlags::IMPORTANT); }
    inline bool isUrgent() const { return 0 != (_flags & ItemFlags::URGENT); }

    inline bool setDone(bool value) {
        _flags = toggle_flag(_flags, ItemFlags::DONE, value);
    }
    inline bool setImportant(bool value) {
        _flags = toggle_flag(_flags, ItemFlags::IMPORTANT, value);
    }
    inline bool setUrgent(bool value) {
        _flags = toggle_flag(_flags, ItemFlags::URGENT, value);
    }

    inline unsigned int flags() const { return _flags; }
    inline void setFlags(int value) { _flags = value; }

private:
    const entityid_t _id;
    const QString _name;
    unsigned int _flags;
};

#endif // ITEM_H
