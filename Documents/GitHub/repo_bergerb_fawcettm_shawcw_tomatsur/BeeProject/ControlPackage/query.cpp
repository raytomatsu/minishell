#include "query.h"
#include <iostream>
#include <vector>
#include <sstream>


/**
 * Query class uses general queries in the database and reformats the results into understandable forms for the controller and GUI.
 */


Query::Query() {

}

Query::Query(DBTool* _tool, DBConfiguration* _config) {
    tool = _tool;
    config = _config;
}


/**
 * @brief Query::queryConfigTableId
 * Query the config table using the details of a hive
 * @return Hive Id
 */
int* Query::query_ConfigTable_Id(string season, int temp, string location) {
     config->select_all_from_temperature_season(temp, season);
     HiveContainer* results = config->list;
     std::vector<Hive*> hivelist = results->get_container();

     int* ids = new int[3];
     for (int i = 0; i < hivelist.size(); i++) {
         int id = (hivelist[i]->getId());
         //add it to our integer array
         ids[i] = id;
     }
     return ids;
}

/**
 * @brief Query::queryConfigTableDetails
 * Query config table using the hive
 * @return an array of hive details
 */
std::string* Query::query_ConfigTable_Details(int id){
    config->select_all();
    config->select_all_from_hiveID(id);
    HiveContainer* results = config->list;
    std::vector<Hive*> hivelist = results->get_container();
    //there will only be one

    std::string* details = new std::string[3];
    Hive* hive = hivelist[0];
    details[0] = hive->getSeason();
    stringstream ss;
    ss << hive->getTemperature();
    details[1] = (ss.str());
    details[2] = hive->getLocation();
    return details;
}

//to generate new hive IDs with no repeats
int Query::query_max_hiveId() {
   //check if its empty
    config->is_it_empty();
    if (config->counter == 0) {
        return 0;
    }
    config->select_max_hiveId();
    return config->maxHiveId;
}

//retrieve all of the UDP messages
activityContainer* Query::retrieve_HiveActivityTable(string tableName){
    DBHive * hivetable = new DBHive(tool, tableName);
    hivetable->select_all();
    return hivetable->list;
}

//retrieve all of the decoded events
EventContainer* Query::retrieve_HiveEventTable(string tableName){
    DBEvent * hivetable = new DBEvent(tool, tableName);
    hivetable->select_all();
    return hivetable->list;
}


