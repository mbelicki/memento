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
