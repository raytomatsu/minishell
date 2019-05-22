#include "hivecontainer.h"
#include <iostream>
#include <string>
#include <sstream>

/**
 * HiveContainer allows a way to return hives from the database.
 */

HiveContainer::HiveContainer()
{

}

HiveContainer::HiveContainer(DBTool* tool, DBConfiguration* _table) {
    dbTool = tool;
    table = _table;
    table->set_list(this);
}

void HiveContainer::add_hive(int argc, char** argv, char** colname) {
//add a new hive object to the container
    int hiveId = std::stoi(argv[0]);
    int temperature = std::stoi(argv[1]);
    std::string season = argv[2];
    std::string location = "do not worry";
    Hive* hive = new Hive(hiveId, season, temperature, location);
    container.push_back(hive);
}

/**
std::string HiveContainer::to_string() {
    std::string ret;
    for (int i = 0; i < container.size(); i++) {
    //id to string
    std::stringstream ss;
    ss << container[i]->getId();
    //get everything in there
    ret.append("Hive Retrieved: ");
    ret.append(ss.str());
    ret.append(", ");
    ret.append(container[i]->getSeason());
    ret.append(", ");
    std::stringstream ss2;
    ss2 << container[i]->getTemperature();
    ret.append(ss2.str());
    ret.append(", ");
    ret.append(container[i]->getLocation());
    ret.append("\n");
    }
    return ret;
}
**/

void HiveContainer::clear() {
    container.clear();
}
