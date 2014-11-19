#ifndef ITEM_H
#define ITEM_H

#include "common.h"

#include <QString>
#include <QDateTime>

class Item
{
public:
    Item(entityid_t id, const QString &name)
        : _id(id)
        , _name(name)
    {}

    Item(const Item &item)
        : _id(item._id)
        , _name(item._name)
    {}

    inline entityid_t id() const { return _id; }
    inline const QString &name() const { return _name; }

private:
    const entityid_t _id;
    const QString _name;
};

#endif // ITEM_H
