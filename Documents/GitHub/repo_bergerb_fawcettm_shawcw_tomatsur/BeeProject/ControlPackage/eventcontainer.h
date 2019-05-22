#ifndef EVENTCONTAINER_H
#define EVENTCONTAINER_H

#include <iostream>
#include <vector>

#include "../DBPackage/dbevent.h"
#include "../DBPackage/dbtool.h"
#include "event.h"

class DBEvent;

class EventContainer
{

public:
    EventContainer();
    EventContainer(DBTool*, DBEvent*);
    void add_event(int argc, char** argv, char** colname);
  //  std::string to_string();
    void clear();    
    std::vector<Event*> get_list();

private:
    DBEvent* table;
    DBTool* tool;
    std::vector<Event*> container;

};
#endif // EVENTCONTAINER_H
