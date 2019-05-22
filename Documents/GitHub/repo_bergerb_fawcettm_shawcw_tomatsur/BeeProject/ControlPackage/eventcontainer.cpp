#include "EventContainer.h"
#include "event.h"
#include <sstream>

/**
 * EventContainer contains several events, in a form to be returned from the database such that the GUI can play real-time data
 * and also use the data to graph.
 */

EventContainer::EventContainer()
{

}

EventContainer::EventContainer(DBTool* _tool, DBEvent* _table) {
    tool = _tool;
    table = _table;
    table->set_list(this);
}

void EventContainer::add_event(int argc, char** argv, char** colname) {
//add a new hive object to the container
    unsigned short id = (unsigned short) std::stoul(argv[0]);
    std::string eep = argv[1];
    unsigned long long time = std::stoull(argv[2]);
    Event* event = new Event(id, time, eep);
    container.push_back(event);
}

/**
//prints out the contents of the eventcontainer
std::string EventContainer::to_string() {
    std::string ret;
    for (int i = 0; i < container.size(); i++) {
    //numbers to stringstream
    std::stringstream ss;
    ss << container[i]->getHiveID();
    ss << ", " << container[i]->getType();
    ss << ", ";
    ss << container[i]->getTime();

    //get everything in there
    ret.append("Event Retrieved: ");
    ret.append(ss.str());
    ret.append("\n");

    }
    return ret;
}
**/

void EventContainer::clear() {
    container.clear();
}

std::vector<Event*> EventContainer::get_list() {
    return container;
}
