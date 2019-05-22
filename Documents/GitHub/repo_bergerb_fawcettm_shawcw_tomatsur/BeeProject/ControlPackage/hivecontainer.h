#ifndef HIVECONTAINER_H
#define HIVECONTAINER_H

#include <iostream>
#include "../DBPackage/dbconfiguration.h"
#include "../DBPackage/dbtool.h"
#include <vector>
#include "hive.h"

class DBConfiguration;

class HiveContainer
{

    /**
      2nd deliverable update -- when hivecontainer and dbconfig implement each other, the code will not compile.
      this is an issue that hasnt yet been sorted out and we can not implement the callback functions until it
      is fixed.
      **/

private:
    DBTool* dbTool;
    DBConfiguration* table;
    std::vector<Hive*> container;

public:
    HiveContainer();
    HiveContainer(DBTool*, DBConfiguration*);
    void add_hive(int argc, char** argv, char** colname);
    std::string to_string();
    void clear();
    std::vector<Hive*> get_container() {return container;}
};

#endif // HIVECONTAINER_H
