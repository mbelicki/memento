#include "listcollection.h"

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
        //calculateColors();
    } else {
        //qDebug() << "allocation failed";
    }
}

void ListCollection::createNewItemInList
            ( entityid_t listId
            , const QString &itemText
            , const QDateTime &itemDueTime
            )
{
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

bool ListCollection::setActiveItem(unsigned int id)
{
    return false;
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

void ListCollection::calculateColors()
{
    int count = _lists.count();
    for (int i = 0; i < count; i++) {
        QColor color;

        const int reverseIndex = count - i;
        const int r = (_topColor.red() * reverseIndex + _bottomColor.red() * i) / count;
        const int g = (_topColor.green() * reverseIndex + _bottomColor.green() * i) / count;
        const int b = (_topColor.blue() * reverseIndex + _bottomColor.blue() * i) / count;

        color.setRgb(r, g, b);

        entityid_t id = _order.at(i);
        TaskList *list = _lists[id];
        list->changeColor(color);
    }
}
