#include "queryhelper.h"


QueryHelper::QueryHelper()
{
    // generate database object
    DBTool *dbtool = new DBTool("TestTableDB");

    // print its state
    dbtool->print(std::cout);

    // generate a new table
    DBHive *ext = new DBHive(dbtool, "TestTable");
    DBConfiguration *exC = new DBConfiguration(dbtool, "TestConfigTwo");

    exC->add_row(0003, "rainy", "fall", "scranton");
    ext->add_row(1, 0003, "hello", 5);
    ext->add_row(2, 0005, "hello", 5);
    ext->add_row(3, 0004, "hello", 5);

    //testing the retrieval of the correct data from the database
    //retrieving hiveID 40 from the collection of activities
    ext->select_all_hiveID(4);
    //show that we have access to the list of Activity objects by using the database functions
    cout << ext->list->to_string() << endl;

    //make sure that the list resets every time we query
    ext->select_all();
    cout << ext->list->to_string() << endl;

    //hiveID 2 from the config table
    exC->select_all();
    //show that we have access to the list of Hive objects by using the database functions
    cout << exC->list->to_string() << endl;

    //config type from the config table
    exC->select_all_from_weather_season_location("rainy", "fall", "scranton");

    //show that the list resets with every query
    //show that we have access to the list of Hive objects by using the database functions
    cout << exC->list->to_string() << endl;

    ext->select_max_hiveID();

    cout << "Max Hive Id =" << ext->maxHiveId << endl;

}

void QueryHelper::ok_button_pressed(){


}
