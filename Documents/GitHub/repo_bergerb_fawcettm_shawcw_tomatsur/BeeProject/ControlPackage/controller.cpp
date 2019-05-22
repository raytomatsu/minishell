#include "controller.h"


#include <iostream>
#include <string>
#include <sstream>

/**
 * @brief Controller::Controller
 *
 * Controller creates a connection between the requests from the GUI to the rest of the system
 * functionality, including the simulation of UDP messages and DB querying.
 */

Controller::Controller()
{
 DBset_up();
}

void Controller::DBset_up() {
    // generate database object
    dbtool = new DBTool("COBDataBase5");
    // print its state
    dbtool->print(std::cout);

    config = new DBConfiguration(dbtool, "ConfigTable");

    query = new Query(dbtool, config);
}

/**
 * For carson.. use this method to create the table for all ur messages. Pass the id
 */
void Controller::create_hiveUDP_table(int hiveId){
    //create string for the hive ID
    std::string tablename = "HiveTable";
    stringstream ss;
    ss << hiveId;
    tablename.append((ss.str()));

    //this is the table for everything for this hive to go into.
    DBHive* hivetable = new DBHive(dbtool, tablename);
}

/**
 * For brett.. use this method to create the table for all ur messages. Pass the id
 */
void Controller::create_hiveEvent_table(int hiveId){
    //create string for the hive ID
    std::string tablename = "EventTable";
    stringstream ss;
    ss << hiveId;
    tablename.append((ss.str()));

    //this is the table for everything for this hive to go into.
    DBEvent* eventtable = new DBEvent(dbtool, tablename);
}

/**
 * for carson, for every activity u make add it using this. pass the hive id so we can find the table
 */
void Controller::add_activity(int hiveId, std::string udp, long long time) {
    //create string for the hive ID
    std::string tablename = "HiveTable";
    stringstream ss;
    ss << hiveId;
    tablename.append((ss.str()));

    //find the table
    DBHive* hivetable = new DBHive(dbtool, tablename);
    //add it
    hivetable->add_row(hivetable->size() + 1, udp, time);
}


/**
 * for brett, for every event u make add it using this. pass the hive id so we can find the table
 * make the id the one that carson uses for his table so theyre unique.
 */
void Controller::add_event(int hiveId, int id, std::string eep, long long time) {
    //create string for the hive ID
    std::string tablename = "EventTable";
    stringstream ss;
    ss << hiveId;
    tablename.append((ss.str()));

    //find the table
    DBEvent* eventtable = new DBEvent(dbtool, tablename);
    //add it
    eventtable->add_row(id, eep, time);

}


//swarm warning detection
bool Controller::check_for_swarm(int entries, int exits, std::string season, int temperature){
    double activityLevel = 1;
    if(season.compare("winter") == 0) activityLevel = 1;
    else if(season.compare("fall") == 0) activityLevel = 1.2;
    else if(season.compare("summer") == 0) activityLevel = 1.4;
    else if(season.compare("spring") == 0) activityLevel = 1.6;
    activityLevel *= temperature;
    activityLevel -= 55;
    activityLevel /= 121.0;

    int swarmThreshold = -5417.5*activityLevel*activityLevel - 4097*activityLevel + 117.79;

    int netChange = entries-exits;
    if(netChange < swarmThreshold)
        return true;
    return false;
}

//robbery detection
bool Controller::check_for_robbery(int entries, int exits, std::string season, int temperature){

    double activityLevel = 1;
    if(season.compare("winter") == 0) activityLevel = 1;
    else if(season.compare("fall") == 0) activityLevel = 1.2;
    else if(season.compare("summer") == 0) activityLevel = 1.4;
    else if(season.compare("spring") == 0) activityLevel = 1.6;
    activityLevel *= temperature;
    activityLevel -= 55;
    activityLevel /= 121.0;

    int robberyThreshold = 6160.9*activityLevel*activityLevel + 3577.6*activityLevel - 88.28;

    int netChange = entries-exits;
    if(netChange > robberyThreshold)
        return true;
    return false;
}


//add hive to the config database
void Controller::add_hive(std::string season, int temp, std::string location) {
    //generate new hive ID
    int max_hiveid = query->query_max_hiveId();
    config->add_row(max_hiveid+1, temp, season, location);
    config->select_all();
   // cout << config->list->to_string() << endl;
}


/**
READ THIS NOW... THIS METHOD REQUESTS INFO FROM THE EVENT TABLE USING HIVE ID. returns a container of events. use that to
ACCESS THE  TIMES AND ALSO what happens at that time. OKAY. okay.
**/
EventContainer* Controller::requestWithId(int hiveId){
    //create string for the hive ID
    std::string tablename = "EventTable";
    stringstream ss;
    ss<<hiveId;
    tablename.append(ss.str());

    //this EventContainer holds all the info we want.
    //from here, maybe we should return the eventcontainer so we can start the sim with it as a parameter.
    EventContainer* events = query->retrieve_HiveEventTable(tablename);
    return events;

}

activityContainer* Controller::retrieve_UDPs(int hiveId) {
    //create string for the hive ID
    std::string tablename = "HiveTable";
    stringstream ss;
    ss<<hiveId;
    tablename.append(ss.str());

    activityContainer* container = query->retrieve_HiveActivityTable(tablename);
    return container;
}


//use params to get the id
int Controller::requestWithPara(std::string season, int temp, std::string loc){
   //returns the id that has these parameters
   int* hive = query->query_ConfigTable_Id(season, temp, loc);
   if (hive[0] == NULL) {
       return -1;
   }
   int hiveId = *hive;

   return hiveId;
}

//use the ID to get the params
std::string* Controller::retrieve_config_details(int hiveId) {
   //returns the details that go along with the ID
    std::string* details = query->query_ConfigTable_Details(hiveId);
    return details;
}

void Controller::startGeneration(std::string season, int temp, std::string swarm) {
    int hiveId = maxId();

}

//when configuring a new hive
void Controller::setCurrentHive(Hive hive) {
    currentHive = hive;

}

Query Controller::getQuery(){
    return *query;
}

int Controller::maxId(){
    return query->query_max_hiveId();
}

