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
