#ifndef TASKLIST_H
#define TASKLIST_H

#include "common.h"
#include "item.h"
#include "ordering.h"

#include <QObject>
#include <QHash>
#include <QColor>

class TaskList : public QObject
{
    Q_OBJECT

    /* nameChanged is never used, defined to remove QML warnings */
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QColor color READ color NOTIFY colorChanged)

public:
    TaskList(entityid_t id, const QString &name, const QColor &color);
    ~TaskList();

    inline entityid_t id() const { return _id; }
    inline const QString &name() const { return _name; }
    inline const QColor &color() const { return _color; }

    bool addItem(const Item &item);
    inline void removeItem(entityid_t id) { _items.remove(id); }

    void changeColor(const QColor &color);

signals:
    void nameChanged();
    void colorChanged();

private:
    const id_t _id;

    QHash<entityid_t, const Item *> _items;
    QString _name;
    QColor _color;
    Ordering _order;
};

#endif // TASKLIST_H
