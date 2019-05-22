#include "dbhive.h"

/**
 * @brief DBHive::DBHive
 *
 * DBHive is a table in our database that holds the information contained in each UDP message
 * received for a specific hive. When received, the UDP message provides information about the activity at a specific
 * time in a specific hive, Time, and Activity. However, it does not
 * contain the information about the hive's details. Those details are contained in the second DB
 * Table, which is DBConfiguration. By using the HiveId to connect these two queries, we can
 * understand how the configuration of a hive lead to the series of activity displayed by the
 * UDP messages.
 *
 */


DBHive::DBHive()
{

}

// Constructor for identying the dbtool and table name.
DBHive::DBHive(DBTool     *db,
                     std::string name   ) :
    DBTable (db, name)
{

    list = new activityContainer(db, this);
    // Load SQL specific to child class.
    store_add_row_sql();
    store_create_sql();

    // must build table sepparately so new
    // sql can be properly registered
    build_table();
}

DBHive::~DBHive() {
}


void DBHive::store_add_row_sql() {

    sql_template =  "SELECT name ";
    sql_template += "FROM   sqlite_master ";
    sql_template += "WHERE";
    sql_template += "    type = \"table\"";
    sql_template += ";";

}


void DBHive::store_create_sql() {

    //std::cerr << "calling store_create_sql from DBHive\n";

    sql_create =  "CREATE TABLE ";
    sql_create += table_name;
    sql_create += " ( ";
    sql_create += "  id INT PRIMARY KEY NOT NULL, ";
    sql_create += "  udpmessage TEXT NOT NULL, ";
    sql_create += "  time UNSIGNED LONG LONG NOT NULL";
    sql_create += " );";

}


bool DBHive::add_row(int id,
                        std::string msg,
                        unsigned long long time) {
    int   retCode = 0;
    char *zErrMsg = 0;

    char  tempval[128];

    sql_add_row  = "INSERT INTO ";
    sql_add_row += table_name;
    sql_add_row += " ( id, udpmessage, time ) ";
    sql_add_row += "VALUES (";

    sprintf (tempval, "%d", id);
    sql_add_row += tempval;
    sql_add_row += ", ";

    sql_add_row += "\"";
    sql_add_row += std::string(msg);
    sql_add_row += "\", ";

    sprintf (tempval, "%llu", time);
    sql_add_row += tempval;

    sql_add_row += " );";

    //std::cout << sql_add_row << std::endl;

    retCode = sqlite3_exec(curr_db->db_ref(),
                           sql_add_row.c_str(),
                           cb_add_rowHIVE,
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


bool DBHive::select_all() {
    //reason we do this is so that our old queries of this DB object are eliminated before recording this query.
    list->clear();

    int   retCode = 0;
    char *zErrMsg = 0;

    sql_select_all  = "SELECT * FROM ";
    sql_select_all += table_name;
    sql_select_all += ";";

    retCode = sqlite3_exec(curr_db->db_ref(),
                           sql_select_all.c_str(),
                           cb_select_allHIVE,
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

int cb_add_rowHIVE(void  *data,
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

    DBHive *obj = (DBHive*) data;

    return 0;
}

int cb_select_allHIVE(void  *data,
                  int    argc,
                  char **argv,
                  char **azColName)
{

    if(argc < 1) {
        std::cerr << "No data presented to callback "
                  << "argc = " << argc
                  << std::endl;
    }

    DBHive *obj = (DBHive*) data;
    //create a container of activity objects out of this
    if(obj->list != nullptr) {
        obj->list->add_activity(argc, argv, azColName);
   }

    return 0;
}


