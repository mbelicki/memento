#ifndef ORDERING_H
#define ORDERING_H

#include "common.h"

#include <QList>

enum orderingmode_t
    { ORD_MANUAL
    , ORD_SORTBY_DATE_DSC
    , ORD_SORTBY_DATE_ACS
    , ORD_SORTBY_COUNT_DSC
    , ORD_SORTBY_COUNT_ACS
    };

class Ordering
{
public:
    Ordering();

    void add(entityid_t newId);
    entityid_t at(int i) const;
    int indexOf(entityid_t id) const;

private:
    orderingmode_t _mode;
    QList<entityid_t> _manualOrder;
};

#endif // ORDERING_H
