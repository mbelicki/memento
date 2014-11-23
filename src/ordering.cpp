#include "ordering.h"

Ordering::Ordering()
{
}

void Ordering::add(entityid_t newId)
{
    _manualOrder.append(newId);
}

entityid_t Ordering::at(int i) const
{
    if (i >= _manualOrder.count())
        return INVALID_ID;

    return _manualOrder.at(i);
}

int Ordering::indexOf(entityid_t id) const
{
    return _manualOrder.indexOf(id);
}
