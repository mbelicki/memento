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

#ifndef DATABASEPERSISTENCE_H
#define DATABASEPERSISTENCE_H

#include <QSqlDatabase>

#include "common.h"
#include "listcollection.h"

class DataBasePersistence
{
public:
    DataBasePersistence();

    bool saveData(const ListCollection &model);
    bool loadData(ListCollection *model);

private:
    QSqlDatabase _base;

    bool saveCollectionData(QSqlQuery *query, const ListCollection &model);
    bool loadCollectionData(QSqlQuery *query, ListCollection *model);
    bool loadLists(QSqlQuery *query, ListCollection *model);
    bool loadTasks(QSqlQuery *query, ListCollection *model);
};

#endif // DATABASEPERSISTENCE_H
