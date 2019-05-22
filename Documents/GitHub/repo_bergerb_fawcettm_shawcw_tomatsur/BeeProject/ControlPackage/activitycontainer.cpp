#include "activitycontainer.h"
#include <sstream>

/**
 * Activity container holds multiple activities in a vector. We use this object to retrieve the activity from the database table and
 * then decode the message
 */


activityContainer::activityContainer()
{

}

activityContainer::activityContainer(DBTool* _tool, DBHive* _table) {
    tool = _tool;
    table = _table;
    table->set_list(this);
}

void activityContainer::add_activity(int argc, char** argv, char** colname) {
//add a new hive object to the container
    int id = std::stoi(argv[0]);
    std::string eep = argv[1];
    long long time = std::stoll(argv[2]);
    Activity* activity = new Activity(id, eep, time);
    container.push_back(activity);
}


//prints out contents of the container
/**
std::string activityContainer::to_string() {
    std::string ret;
    for (int i = 0; i < container.size(); i++) {
    //numbers to stringstream
    std::stringstream ss;
    ss << container[i]->getId();
    ss << ", " << container[i]->getEntryExitPeak();
    ss << ", ";
    ss << container[i]->getTime();

    //get everything in there
    ret.append("Activity Retrieved: ");
    ret.append(ss.str());
    ret.append("\n");

    }
    return ret;
}
**/

void activityContainer::clear() {
    container.clear();
}



std::vector<Activity*> activityContainer::getContainer(){
    return container;
}
