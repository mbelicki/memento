#ifndef LISTWRAPPER_H
#define LISTWRAPPER_H

#include "listcollection.h"

#include <QAbstractListModel>

class ListsListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    ListsListModel(ListCollection *collection);

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void addTaskList(const QString &name, const QColor &color);

private slots:
    void itemChanged(entityid_t id);

private:
    enum Roles
        { NameRole = Qt::UserRole + 1
        , ColorRole
        , IdRole
        , SizeRole
        , DoneCountRole
        };

    ListCollection *_collection;

};

#endif // LISTWRAPPER_H
