#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "hive.h"
#include "../DBPackage/dbhive.h"
#include "../DBPackage/dbconfiguration.h"
#include "../DBPackage/dbtool.h"
#include "hivecontainer.h"
#include "query.h"
#include "eventcontainer.h"

class Controller
{
public:
    Controller();
    void setCurrentHive(Hive hive);
    void DBset_up();

    void create_hiveUDP_table(int hiveId);
    void create_hiveEvent_table(int hiveId);

    void add_activity(int hiveId, std::string udp, long long time);
    void add_event(int hiveId, int id, std::string eep, long long time);

    EventContainer* requestWithId(int);
    int requestWithPara(std::string, int, std::string);

    void add_hive(std::string, int, std::string);
    bool check_for_swarm(int, int, std::string season, int temperature);
    bool check_for_robbery(int, int, std::string season, int temperature);
    activityContainer* retrieve_UDPs(int hiveId);

   std::string* retrieve_config_details(int hiveId);
    Query getQuery();
    int maxId();

    void startGeneration(std::string season, int temp, std::string swarm);

private:
    Hive currentHive;
    Query *query;
    DBTool *dbtool;
    DBHive *activity;
    DBConfiguration *config;
};

#endif // CONTROLLER_H
