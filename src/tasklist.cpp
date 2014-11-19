#include "tasklist.h"

TaskList::TaskList(entityid_t id, const QString &name, const QColor &color)
    : _id(id)
    , _name(name)
    , _color(color)
{
}

TaskList::~TaskList()
{
   /* delete items */
}

bool TaskList::addItem(const Item &item)
{
    const Item *ownedItem = new (std::nothrow) Item(item);
    if (ownedItem == NULL) return false;

    _items.insert(ownedItem->id(), ownedItem);
    emit sizeChanged();

    return true;
}

void TaskList::changeColor(const QColor &color)
{
    if (_color != color) {
        _color = color;
        colorChanged();
    }
}

