#ifndef ACTIVITYCONTAINER_H
#define ACTIVITYCONTAINER_H
#include <iostream>
#include <vector>

#include "../DBPackage/dbhive.h"
#include "../DBPackage/dbtool.h"
#include "../ControlPackage/activity.h"

class DBHive;

class activityContainer
{
    /**
      2nd deliverable update -- when activitycontainer and dbhive implement each other, the code will not compile.
      this is an issue that hasnt yet been sorted out and we can not implement the callback functions until it
      is fixed.
   **/

public:
    activityContainer();
    activityContainer(DBTool*, DBHive*);
    void add_activity(int argc, char** argv, char** colname);
   // std::string to_string();
    void clear();

    std::vector<Activity*> getContainer();

private:
    DBHive* table;
    DBTool* tool;
    std::vector<Activity*> container;

};

#endif // ACTIVITYCONTAINER_H
