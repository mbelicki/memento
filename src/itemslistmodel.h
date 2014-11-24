#ifndef ITEMSLISTMODEL_H
#define ITEMSLISTMODEL_H

#include "tasklist.h"
#include "listcollection.h"

#include <QAbstractListModel>

class ItemsListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QColor color READ color NOTIFY colorChanged)
    Q_PROPERTY(int size READ size NOTIFY sizeChanged)
    Q_PROPERTY(int doneCount READ doneCount NOTIFY doneCountChanged)

public:
    ItemsListModel(TaskList *list, ListCollection *collection)
        : _list(list)
        , _collection(collection)
    {}

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void createItem(const QString &name);
    Q_INVOKABLE void setChecked(int index, bool value);

    inline const QString &name() const { return _list->name(); }
    inline const QColor &color() const { return _list->color(); }
    inline int size() const { return _list->size(); }
    inline int doneCount() const { return _list->doneCount(); }

signals:
    void nameChanged();
    void colorChanged();
    void sizeChanged();
    void doneCountChanged();

private:
    enum Roles
        { NameRole = Qt::UserRole + 1
        , IdRole
        , DoneRole
        };

    TaskList *_list;
    ListCollection *_collection;

};

#endif // ITEMSLISTMODEL_H
