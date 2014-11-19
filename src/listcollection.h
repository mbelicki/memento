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

    Q_INVOKABLE void createNewList
            ( const QString &name
            , const QColor &color
            );
    void createNewItemInList
            ( entityid_t listId
            , const QString &itemText
            , const QDateTime &itemDueTime
            );

    Q_INVOKABLE QList<QObject *> getOrderedLists() const;
    Q_INVOKABLE bool setActiveList(unsigned int /*entityid_t*/ id);
    Q_INVOKABLE bool setActiveItem(unsigned int /*entityid_t*/ id);

    inline QObject *activeList() const { return _activeList; }

    const TaskList *at(int index) const;

    inline int count() const { return _lists.count(); }

signals:
    void activeListChanged();

private:
    QHash<entityid_t, TaskList *> _lists;
    Ordering _order;

    entityid_t _nextId;
    QColor _topColor;
    QColor _bottomColor;

    TaskList *_activeList;

    entityid_t getNextId();
    void calculateColors();
};

#endif // LISTCOLLECTION_H
