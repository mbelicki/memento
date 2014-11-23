#include "listcollection.h"

#include "itemslistmodel.h"

ListCollection::ListCollection()
    : _lists()
    , _order()
    , _nextId(0)
    , _activeList(NULL)
{
}

ListCollection::~ListCollection()
{
    QHash<entityid_t, TaskList *>::const_iterator itl;
    for (itl = _lists.constBegin(); itl != _lists.constEnd(); itl++) {
        delete *itl;
    }
    _lists.clear();

    QHash<entityid_t, Item *>::const_iterator iti;
    for (iti = _items.constBegin(); iti != _items.constEnd(); iti++) {
        delete *iti;
    }
    _items.clear();
}

const TaskList *ListCollection::createAndAddNewList
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
    return list;
}

void ListCollection::createNewItemInList
            (entityid_t listId
            , const QString &itemName
            )
{
    if (_lists.contains(listId) == false)
        return;

    Item *item = new Item(getNextId(), itemName, false);
    _items[item->id()] = item;
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

const TaskList *ListCollection::byId(entityid_t id) const
{
    const TaskList *result = NULL;
    if (_lists.contains(id))
        result = _lists[id];
    return result;
}

bool ListCollection::setChecked(entityid_t itemId, bool value)
{
    if (_items.contains(itemId) == false)
        return false;

    _items[itemId]->setDone(value);
    return true;
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

bool ListCollection::insertList
        (entityid_t id, const QString &name, const QColor &color)
{
    TaskList *list = new (std::nothrow) TaskList(id, name, color);
    if (list != NULL) {
        _lists.insert(id, list);
        _order.add(id);
    }
}

bool ListCollection::insertItem
        (entityid_t id, const QString &name, bool done, entityid_t parentId)
{
    Item *item = new Item(id, name, done);
    _items[item->id()] = item;
    _lists[parentId]->addItem(item);
}
