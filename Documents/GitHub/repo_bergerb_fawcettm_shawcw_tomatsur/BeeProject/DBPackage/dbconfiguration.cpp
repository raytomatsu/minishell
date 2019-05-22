#include "dbconfiguration.h"
#include <sstream>
#include <iostream>


/**
 * @brief DBConfiguration::DBConfiguration
 *
 * DBConfiguration contains the data that was used to configure a specific hive. When the simulation
 * of a hive is started, it begins by taking into account various pieces of data like weather,
 * season, and location. The timing of UDP messages will be based off of these pieces of info.
 * By containing this information in this DBTable, we can then connect the activity contained in
 * DBHive with some of the factors that contributed to the UDP messages.
 */


DBConfiguration::DBConfiguration()
{

}

// Constructor for identying the dbtool and table name.
DBConfiguration::DBConfiguration(DBTool     *db,
                     std::string name   ) :
    DBTable (db, name)
{
    list = new HiveContainer(db, this);
    // Load SQL specific to child class.
    store_add_row_sql();
    store_create_sql();

    // must build table sepparately so new
    // sql can be properly registered
    build_table();
}

DBConfiguration::~DBConfiguration() {
}


void DBConfiguration::store_add_row_sql() {

    sql_template =  "SELECT name ";
    sql_template += "FROM   sqlite_master ";
    sql_template += "WHERE";
    sql_template += "    type = \"table\"";
    sql_template += ";";

}


void DBConfiguration::store_create_sql() {

    //std::cerr << "calling store_create_sql from DBConfiguration\n";

    sql_create =  "CREATE TABLE ";
    sql_create += table_name;
    sql_create += " ( ";
    sql_create += "  hiveId INT PRIMARY KEY NOT NULL, ";
    sql_create += "  temperature INT NOT NULL, ";
    sql_create += "  season TEXT NOT NULL, ";
    sql_create += "  location TEXT NOT NULL";
    sql_create += " );";

}


bool DBConfiguration::add_row(int id, int temperature,
                        std::string season,
                        std::string location) {
    int   retCode = 0;
    char *zErrMsg = 0;

    counter++;

    char  tempval[128];

    sql_add_row  = "INSERT INTO ";
    sql_add_row += table_name;
    sql_add_row += " ( hiveId, temperature, season, location ) ";
    sql_add_row += "VALUES (";

    sprintf (tempval, "%d", id);
    sql_add_row += tempval;
    sql_add_row += ", ";

    sprintf (tempval, "%d", temperature);
    sql_add_row += tempval;
    sql_add_row += ", ";

    sql_add_row += "\"";
    sql_add_row += std::string(season);
    sql_add_row += "\", ";

    sql_add_row += "\"";
    sql_add_row += std::string(location);
    sql_add_row += "\"";
    sql_add_row += " );";

    //std::cout << sql_add_row << std::endl;

    retCode = sqlite3_exec(curr_db->db_ref(),
                           sql_add_row.c_str(),
                           cb_add_row,
                           this,
                           &zErrMsg          );
    if( retCode != SQLITE_OK ){

        std::cerr << table_name
                  << " template ::"
                  << std::endl
                  << "SQL error: "
                  << zErrMsg;

        sqlite3_free(zErrMsg);
    }

    return retCode;
}


bool DBConfiguration::select_all() {
    //reason we do this is so that our old queries of this DB object are eliminated before recording this query.
    list->clear();
    int   retCode = 0;
    char *zErrMsg = 0;

    sql_select_all  = "SELECT * FROM ";
    sql_select_all += table_name;
    sql_select_all += ";";

    retCode = sqlite3_exec(curr_db->db_ref(),
                           sql_select_all.c_str(),
                           cb_select_all,
                           this,
                           &zErrMsg          );

    if( retCode != SQLITE_OK ){

        std::cerr << table_name
                  << " template ::"
                  << std::endl
                  << "SQL error: "
                  << zErrMsg;

        sqlite3_free(zErrMsg);
    }

    return retCode;
}

//select a hive based on id
bool DBConfiguration::select_all_from_hiveID(int hiveID) {
    //reason we do this is so that our old queries of this DB object are eliminated before recording this query.
    list->clear();
    int   retCode = 0;
    char *zErrMsg = 0;

    sql_select_all  = "SELECT * FROM ";
    sql_select_all += table_name;
    sql_select_all += " WHERE hiveId=" + std::to_string(hiveID) + ";";

    retCode = sqlite3_exec(curr_db->db_ref(),
                           sql_select_all.c_str(),
                           cb_select_all,
                           this,
                           &zErrMsg          );

    if( retCode != SQLITE_OK ){

        std::cerr << table_name
                  << " template ::"
                  << std::endl
                  << "SQL error: "
                  << zErrMsg;

        sqlite3_free(zErrMsg);
    }

    return retCode;
}


//select a hive from a wsl configuration
bool DBConfiguration::select_all_from_temperature_season(int temp, std::string season){
    //reason we do this is so that our old queries of this DB object are eliminated before recording this query.
    list->clear();
    int   retCode = 0;
    char *zErrMsg = 0;

    std::stringstream ss;
    ss << temp;
    sql_select_tsl  = "SELECT * FROM ";
    sql_select_tsl += table_name;
    sql_select_tsl += " WHERE temperature='" + ss.str() + "' AND season='" + season + "';";

    retCode = sqlite3_exec(curr_db->db_ref(),
                           sql_select_tsl.c_str(),
                           cb_select_all,
                           this,
                           &zErrMsg          );

    if( retCode != SQLITE_OK ){

        std::cerr << table_name
                  << " template ::"
                  << std::endl
                  << "SQL error: "
                  << zErrMsg;

        sqlite3_free(zErrMsg);
    }

    return retCode;
}

bool DBConfiguration::select_max_hiveId() {

    int   retCode = 0;
    char *zErrMsg = 0;

    sql_select_max  = "SELECT max(hiveId) FROM ";
    sql_select_max += table_name;
    sql_select_max += ";";

    retCode = sqlite3_exec(curr_db->db_ref(),
                           sql_select_max.c_str(),
                           cb_select_max,
                           this,
                           &zErrMsg          );

    if( retCode != SQLITE_OK ){

        std::cerr << table_name
                  << " template ::"
                  << std::endl
                  << "SQL error: "
                  << zErrMsg;

        sqlite3_free(zErrMsg);
    }

    return retCode;
}

bool DBConfiguration::is_it_empty() {

    int   retCode = 0;
    char *zErrMsg = 0;

    sql_select_max  = "SELECT EXISTS (SELECT 1 FROM " + table_name + ");";

    retCode = sqlite3_exec(curr_db->db_ref(),
                           sql_select_max.c_str(),
                           cb_is_it_empty,
                           this,
                           &zErrMsg          );

    if( retCode != SQLITE_OK ){

        std::cerr << table_name
                  << " template ::"
                  << std::endl
                  << "SQL error: "
                  << zErrMsg;

        sqlite3_free(zErrMsg);
    }

    return retCode;
}


int cb_add_row(void  *data,
               int    argc,
               char **argv,
               char **azColName)
{



    if(argc < 1) {
        std::cerr << "No data presented to callback "
                  << "argc = " << argc
                  << std::endl;
    }

    int i;

    DBConfiguration *obj = (DBConfiguration*) data;

    return 0;
}


int cb_select_all(void  *data,
                  int    argc,
                  char **argv,
                  char **azColName)
{

    if(argc < 1) {
        std::cerr << "No data presented to callback "
                  << "argc = " << argc
                  << std::endl;
    }

    int i;

    DBConfiguration* obj = (DBConfiguration *) data;

    //create a container of hive objects out of this

    if(obj->list != nullptr) {
        obj->list->add_hive(argc, argv, azColName);
   }

    return 0;
}

int cb_select_max(void  *data,
                  int    argc,
                  char **argv,
                  char **azColName)
{

    if(argc < 1) {
        std::cerr << "No data presented to callback "
                  << "argc = " << argc
                  << std::endl;
    }

    DBConfiguration *obj = (DBConfiguration*) data;

    if (argv[0] != NULL) {
     obj->maxHiveId = std::stoi(argv[0]);
    }

    return 0;
}

int cb_is_it_empty(void  *data,
                  int    argc,
                  char **argv,
                  char **azColName)
{

    if(argc < 1) {
        std::cerr << "No data presented to callback "
                  << "argc = " << argc
                  << std::endl;
    }

    DBConfiguration *obj = (DBConfiguration*) data;


     obj->counter = std::stoi(argv[0]);


    return 0;
}


