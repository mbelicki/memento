/*
 * Copyright 2014 Mateusz Belicki
 *
 * free.software@belickim.net
 *
 * This file is part of Memento (Sailfish OS todo app).
 *
 * Memento is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * Memento is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Memento. If not, see <http://www.gnu.org/licenses/>.
 */

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
