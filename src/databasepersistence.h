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
