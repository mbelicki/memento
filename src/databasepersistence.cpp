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

#include "databasepersistence.h"

#include <QDir>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>

static const char *const NEXT_ID_KEY = "next_id";

/* TODO: automatically check if all columns are present before loading,
 * add missing ones otherwise. Use: PRAGMA table_info('table_name')
 * to get column names */
struct column_t {
    const char *name;
    const char *type;
};

const column_t LISTS_COLUMNS[]
    = { {"id", "INT PRIMATY KEY"}
      , {"name", "VARCHAR(256)"}
      , {"color", "VARCHAR(16)"}
      };

const column_t TASKS_COLUMNS[]
    = { {"id", "INT PRIMATY KEY"}
      , {"name", "VARCHAR(256)"}
      , {"status", "INT"}
      , {"list_id", "INT"}
      };

inline static void logSqlError(const QSqlError &error, const char *message) {
    qCritical() << message << error.databaseText() << error.driverText();
}

static bool createTables(QSqlQuery *query) {
    M_CHECK_PTR_ARG(query, false)

    bool result = false;

    result = query->exec( "CREATE TABLE IF NOT EXISTS tasks"
                          " ( id INT PRIMARY KEY"
                          " , name VARCHAR(256)"
                          " , status INT"
                          " , list_id INT"
                          " )"
                        );
    if (result == false) {
        logSqlError(query->lastError(), "Failed to create 'tasks' table:");
        return false;
    }

    result = query->exec( "CREATE TABLE IF NOT EXISTS lists"
                          " ( id INT PRIMARY KEY"
                          " , name VARCHAR(256)"
                          " , color VARCHAR(16)"
                          " )"
                        );
    if (result == false) {
        logSqlError(query->lastError(), "Failed to create 'lists' table:");
    }

    result = query->exec( "CREATE TABLE IF NOT EXISTS collectionData"
                          " ( key VARCHAR(256) PRIMARY KEY"
                          " , value VARCHAR(256)"
                          " )"
                        );
    return true;
}

static bool insertList(QSqlQuery *query, const TaskList* list) {
    M_CHECK_PTR_ARG(query, false)
    M_CHECK_PTR_ARG(list, false)

    query->prepare("INSERT OR REPLACE INTO lists VALUES(:id, :name, :color)");
    query->bindValue(":id", list->id());
    query->bindValue(":name", list->name());
    query->bindValue(":color", list->color().name());

    bool result = query->exec();
    if (result == false) {
        logSqlError(query->lastError(), "Failed to insert new list:");
        return false;
    }
    return true;
}

static bool insertTask(QSqlQuery *query, const Item* task, entityid_t listId) {
    M_CHECK_PTR_ARG(query, false)
    M_CHECK_PTR_ARG(task, false)

    query->prepare("INSERT OR REPLACE INTO tasks VALUES(:id, :name, :status, :listId)");
    query->bindValue(":id", task->id());
    query->bindValue(":name", task->name());
    query->bindValue(":status", task->flags());
    query->bindValue(":listId", listId);

    bool result = query->exec();
    if (result == false) {
        logSqlError(query->lastError(), "Failed to insert new task:");
        return false;
    }
    return true;
}

DataBasePersistence::DataBasePersistence()
    : _base(QSqlDatabase::addDatabase("QSQLITE"))
{
    /* the data dir is: /home/nemo/.local/share/memento/memento */

    const QString baseDir = QDir::homePath() + "/.local/share/memento/memento";
    QDir::home().mkpath(".local/share/memento/memento");

    const QString basePath = baseDir + "/base.v0.db";
    _base.setDatabaseName(basePath); //(":memory:");
}

bool DataBasePersistence::saveData(const ListCollection &model)
{
    bool openResult = _base.open();
    if (openResult == false) {
        QSqlError error = _base.lastError();
        qCritical() << "Failed to open data base while saving:"
                    << error.databaseText()
                    << error.driverText();
        return false;
    }

    QSqlQuery query(_base);
    bool createResult = createTables(&query);
    if (createResult == false) {
        qCritical() << "Failed to create tables.";
        return false;
    }

    bool dataSaveResult = saveCollectionData(&query, model);
    if (dataSaveResult == false) {
        qCritical() << "Failed to save collection data.";
        return false;
    }

    for (int i = 0; i < model.size(); i++) {
        const TaskList *list = model.at(i);
        if (list == NULL) continue;
        insertList(&query, list);

        for (int j = 0; j < list->size(); j++) {
            const Item *item = list->at(j);
            if (item == NULL) continue;
            insertTask(&query, item, list->id());
        }
    }

    _base.close();
    return true;
}

bool DataBasePersistence::loadData(ListCollection *model)
{
    (void) model;
    bool openResult = _base.open();
    if (openResult == false) {
        QSqlError error = _base.lastError();
        qCritical() << "Failed to open data base while loading:"
                    << error.databaseText()
                    << error.driverText();
        return false;
    }

    QSqlQuery query(_base);

    loadCollectionData(&query, model);

    const bool loadListsResult = loadLists(&query, model);
    if (loadListsResult == false) {
        qCritical() << "Failed to load lists.";
        return false;
    }

    const bool loadTasksResult = loadTasks(&query, model);
    if (loadTasksResult == false) {
        qCritical() << "Failed to load tasks.";
        return false;
    }

    _base.close();
    return true;
}

bool DataBasePersistence::saveCollectionData
        (QSqlQuery *query, const ListCollection &model)
{
    M_CHECK_PTR_ARG(query, false)

    query->prepare("INSERT OR REPLACE INTO collectionData VALUES(:key, :value)");
    query->bindValue(":key", NEXT_ID_KEY);
    query->bindValue(":value", model.lastId());

    bool result = query->exec();
    if (result == false) {
        logSqlError(query->lastError(), "Failed to insert next_id:");
        return false;
    }
    return true;
}

bool DataBasePersistence::loadCollectionData
        (QSqlQuery *query, ListCollection *model)
{
    M_CHECK_PTR_ARG(query, false)
    M_CHECK_PTR_ARG(model, false)

    const bool selectResult = query->exec("SELECT * FROM collectionData");
    if (selectResult == false) {
        logSqlError(query->lastError(), "Failed to select data from 'collectionData':");
        return false;
    }

    const int keyIndex   = query->record().indexOf("key");
    const int valueIndex = query->record().indexOf("value");

    while (query->next()) {
        const QString key = query->value(keyIndex).toString();
        const QString value = query->value(valueIndex).toString();
        if (key == NEXT_ID_KEY) {
            qDebug() << "Found" << NEXT_ID_KEY << ":" << value;
            model->setLastId((entityid_t)value.toLongLong());
        }
    }
    return true;
}

bool DataBasePersistence::loadLists
        (QSqlQuery *query, ListCollection *model)
{
    M_CHECK_PTR_ARG(query, false)
    M_CHECK_PTR_ARG(model, false)

    const bool selectResult = query->exec("SELECT * FROM lists");
    if (selectResult == false) {
        logSqlError(query->lastError(), "Failed to select data from 'lists':");
        return false;
    }

    const int nameIndex  = query->record().indexOf("name");
    const int colorIndex = query->record().indexOf("color");
    const int idIndex    = query->record().indexOf("id");

    while (query->next()) {
        const entityid_t id = (entityid_t)query->value(idIndex).toLongLong();
        const QString name = query->value(nameIndex).toString();
        const QColor color = QColor(query->value(colorIndex).toString());
        model->insertList(id, name, color);
    }
    return true;
}

bool DataBasePersistence::loadTasks
        (QSqlQuery *query, ListCollection *model)
{
    M_CHECK_PTR_ARG(query, false)
    M_CHECK_PTR_ARG(model, false)

    const bool selectResult = query->exec("SELECT * FROM tasks");
    if (selectResult == false) {
        logSqlError(query->lastError(), "Failed to select data from 'tasks':");
        return false;
    }

    const int nameIndex   = query->record().indexOf("name");
    const int idIndex     = query->record().indexOf("id");
    const int statusIndex = query->record().indexOf("status");
    const int parentIndex = query->record().indexOf("list_id");

    while (query->next()) {
        const entityid_t id = (entityid_t)query->value(idIndex).toLongLong();
        const QString name = query->value(nameIndex).toString();
        const int status = query->value(statusIndex).toUInt();
        const entityid_t parent = (entityid_t)query->value(parentIndex).toLongLong();
        model->insertItem(id, name, status, parent);
    }
    return true;
}
