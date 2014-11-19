#ifndef ITEM_H
#define ITEM_H

#include "common.h"

#include <QString>
#include <QDateTime>

class Item
{
public:
    Item(entityid_t id, const QString &text, const QDateTime duetime)
        : _id(id)
        , _text(text)
    {}

    Item(const Item &item)
        : _id(item.getId())
        , _text(item.getText())
    {}

    inline entityid_t getId() const { return _id; }
    inline const QString &getText() const { return _text; }

private:
    const entityid_t _id;
    const QString _text;
};

#endif // ITEM_H
