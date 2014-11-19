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
    const entityid_t id = item.id();

    const Item *ownedItem = new (std::nothrow) Item(item);
    if (ownedItem == NULL) return false;

    _items.insert(id, ownedItem);
    _order.add(id);
    emit sizeChanged();

    return true;
}

const Item *TaskList::at(int i) const
{
    const entityid_t id = _order.at(i);
    return _items[id];
}

void TaskList::changeColor(const QColor &color)
{
    if (_color != color) {
        _color = color;
        colorChanged();
    }
}

