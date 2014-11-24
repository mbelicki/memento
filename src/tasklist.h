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

#ifndef TASKLIST_H
#define TASKLIST_H

#include "common.h"
#include "item.h"
#include "ordering.h"

#include <QObject>
#include <QHash>
#include <QColor>

class TaskList : public QObject
{
    Q_OBJECT

    /* nameChanged is never used, defined to remove QML warnings */
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QColor color READ color NOTIFY colorChanged)
    Q_PROPERTY(int size READ size NOTIFY sizeChanged)
    Q_PROPERTY(int doneCount READ doneCount NOTIFY doneCountChanged)

public:
    TaskList(entityid_t id, const QString &name, const QColor &color);
    ~TaskList() {}

    inline entityid_t id() const { return _id; }
    inline const QString &name() const { return _name; }
    inline const QColor &color() const { return _color; }
    inline int size() const { return _items.size(); }
    inline int doneCount() const { return _doneCount; }

    bool addItem(const Item *item);
    inline void removeItem(entityid_t id) {
        _items.remove(id);
        emit sizeChanged(_id);
    }

    const Item *at(int i) const;

    void changeColor(const QColor &color);
    void updateDoneCount();

signals:
    void nameChanged(entityid_t sender);
    void colorChanged(entityid_t sender);
    void sizeChanged(entityid_t sender);
    void doneCountChanged(entityid_t sender);

private:
    const entityid_t _id;

    QHash<entityid_t, const Item *> _items;
    QString _name;
    QColor _color;
    Ordering _order;
    int _doneCount;
};

#endif // TASKLIST_H
