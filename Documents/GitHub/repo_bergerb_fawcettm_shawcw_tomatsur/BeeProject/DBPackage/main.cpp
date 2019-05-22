#include <iostream>
#include "dbtool.h"
#include "dbtable.h"
#include "dbhive.h"
#include "dbconfiguration.h"
#include "dbevent.h"

using namespace std;

int main()
{
    // generate database object
    DBTool *dbtool = new DBTool("TestTableDB");

    // print its state
    dbtool->print(std::cout);

    // generate a new table
    DBHive *ext = new DBHive(dbtool, "TestTable2");
    DBConfiguration *exC = new DBConfiguration(dbtool, "TestConfig3");
    DBEvent *exE = new DBEvent(dbtool, "event");

    exC->add_row(0007, 4, "fall", "scranton");
    exC->add_row(0005, 50, "spring", "rayTown");

    exE->add_row(4, "entry", 5);
    exE->add_row(5, "exit", 6);
    exE->add_row(6, "peak", 7);

    ext->add_row(005, "something", 98);

    ext->select_all();
    //show that we have access to the list of Activity objects by using the database functions
    //cout << ext->list->to_string() << endl;

    //make sure that the list resets every time we query
    exE->select_all();
    //cout << exE->list->to_string() << endl;

    //hiveID 2 from the config table
    exC->select_all();
    //show that we have access to the list of Hive objects by using the database functions
 //   cout << exC->list->to_string() << endl;


    //config type from the config table
    //exC->select_all_from_temperature_season_location(4, "fall", "scranton");

    //show that the list resets with every query
    //show that we have access to the list of Hive objects by using the database functions
//    cout << exC->list->to_string() << endl;

    exC->select_max_hiveId();

  //  cout << "Max Hive Id =" << exC->maxHiveId << endl;

}
