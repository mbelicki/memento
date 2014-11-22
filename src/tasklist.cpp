#include "tasklist.h"

TaskList::TaskList(entityid_t id, const QString &name, const QColor &color)
    : _id(id)
    , _items()
    , _name(name)
    , _color(color)
    , _order()
    , _doneCount(0)
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
    emit sizeChanged(_id);

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
        emit colorChanged(_id);
    }
}

void TaskList::updateDoneCount()
{
    int count = 0;
    QHash<entityid_t, const Item *>::const_iterator it;
    for (it = _items.constBegin(); it != _items.constEnd(); it++) {
        count += (*it)->isDone();
    }

    if (count != _doneCount){
        _doneCount = count;
        emit doneCountChanged(_id);
    }
}
