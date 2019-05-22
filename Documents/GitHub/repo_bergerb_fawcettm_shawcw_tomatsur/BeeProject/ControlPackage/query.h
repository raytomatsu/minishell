#ifndef QUERY_H
#define QUERY_H

#include <string>
#include "hive.h"
#include <vector>

#include "../DBPackage/dbhive.h"
#include "../DBPackage/dbconfiguration.h"
#include "../DBPackage/dbtool.h"
#include "hivecontainer.h"
#include "activitycontainer.h"
#include "eventcontainer.h"

using namespace std;

class Query
{
public:
    Query();
    Query(DBTool* tool, DBConfiguration* config);

    int* query_ConfigTable_Id(string season, int temp, string location); //using details
    std::string* query_ConfigTable_Details(int id); //using Id

    activityContainer* retrieve_HiveActivityTable(string tableName);
    EventContainer* retrieve_HiveEventTable(string tableName);

    int query_max_hiveId();
    //hive

private:
    std::vector<Hive*> currentHives;
    DBTool* tool;
    DBConfiguration* config;

};

#endif // QUERY_H
