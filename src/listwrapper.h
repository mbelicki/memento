#ifndef LISTWRAPPER_H
#define LISTWRAPPER_H

#include "listcollection.h"

#include <QAbstractListModel>

class ListWrapper : public QAbstractListModel
{
    Q_OBJECT
public:
    ListWrapper(ListCollection *collection)
        : _collection(collection)
    {}

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

signals:

public slots:

private:
    enum Roles
        { NameRole = Qt::UserRole + 1
        , ColorRole
        , IdRole
        };

    ListCollection *_collection;

};

#endif // LISTWRAPPER_H
