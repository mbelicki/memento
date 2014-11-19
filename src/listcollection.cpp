#include "listcollection.h"

#include "itemslistmodel.h"

ListCollection::ListCollection()
    : _topColor(QColor("red"))
    , _bottomColor(QColor("yellow"))
    , _activeList(NULL)
{
}

ListCollection::~ListCollection()
{
    QHash<entityid_t, TaskList *>::const_iterator it;
    for (it = _lists.constBegin(); it != _lists.constEnd(); it++) {
        delete it.value();
    }
    _lists.clear();
}

void ListCollection::createNewList
    ( const QString &name
    , const QColor &color
    )
{
    entityid_t id = getNextId();
    TaskList *list = new (std::nothrow) TaskList(id, name, color);
    if (list != NULL) {
        _lists.insert(id, list);
        _order.add(id);
    }
}

void ListCollection::createNewItemInList
            (entityid_t listId
            , const QString &itemName
            )
{
    if (_lists.contains(listId) == false)
        return;

    Item item(getNextId(), itemName);
    _lists[listId]->addItem(item);

}

bool ListCollection::setActiveList(unsigned int id)
{
    bool result = false;

    TaskList *oldValue = _activeList;

    if (_lists.contains(id)) {
        _activeList = _lists[id];
        result = true;
    } else {
        _activeList = NULL;
    }

    if (oldValue != _activeList) {
        activeListChanged();
    }

    return result;
}

QObject *ListCollection::createListModel(unsigned int id)
{
    if (_lists.contains(id) == false)
        return NULL;
    return new ItemsListModel(_lists[id], this);
}

const TaskList *ListCollection::at(int index) const
{
    if (index >= _lists.count())
        return NULL;

    entityid_t id = _order.at(index);
    return _lists[id];
}

QList<QObject *> ListCollection::getOrderedLists() const
{
    QList<QObject *> result;
    QHash<entityid_t, TaskList *>::const_iterator it;
    for (it = _lists.constBegin(); it != _lists.constEnd(); it++) {
        result.append(it.value());
    }
    return result;
}

entityid_t ListCollection::getNextId()
{
    entityid_t id = _nextId;
    _nextId++;
    return id;
}
