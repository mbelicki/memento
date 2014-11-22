#ifndef LISTCOLLECTION_H
#define LISTCOLLECTION_H

#include "common.h"
#include "tasklist.h"
#include "ordering.h"

#include <QObject>
#include <QHash>
#include <QVariantList>
#include <QAbstractListModel>

class ListCollection : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QObject* activeList READ activeList NOTIFY activeListChanged)

public:
    ListCollection();
    ~ListCollection();

    Q_INVOKABLE const TaskList *createAndAddNewList
            ( const QString &name
            , const QColor &color
            );
    Q_INVOKABLE void createNewItemInList
            ( entityid_t listId
            , const QString &itemName
            );

    Q_INVOKABLE bool setActiveList(unsigned int /*entityid_t*/ id);
    Q_INVOKABLE QObject *createListModel(unsigned int id);

    Q_INVOKABLE QList<QObject *> getOrderedLists() const;
    inline QObject *activeList() const { return _activeList; }

    const TaskList *at(int index) const;
    const TaskList *byId(entityid_t id) const;
    int indexOf(entityid_t id) const { return _order.indexOf(id); }

    inline int size() const { return _lists.size(); }

signals:
    void activeListChanged();

private:
    QHash<entityid_t, TaskList *> _lists;
    Ordering _order;
    entityid_t _nextId;
    TaskList *_activeList;

    entityid_t getNextId();
};

#endif // LISTCOLLECTION_H
