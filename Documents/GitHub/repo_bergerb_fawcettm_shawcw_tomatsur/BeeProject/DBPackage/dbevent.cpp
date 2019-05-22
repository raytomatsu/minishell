#include "dbEvent.h"


/**
 * @brief DBEvent::DBEvent
 *
 * DBEvent is the partner to each DBHive table. the DBHive tables hold the UDP messages that the hive has produced, and the DBEvent table
 * holds these messages in their decoded form, holding the info about what events happened at what time. this info is what is used by the c
 * controller to display data about hive activity on the GUI.
 */


DBEvent::DBEvent()
{

}

// Constructor for identying the dbtool and table name.
DBEvent::DBEvent(DBTool     *db,
                     std::string name   ) :
    DBTable (db, name)
{

    list = new EventContainer(db, this);
    // Load SQL specific to child class.
    store_add_row_sql();
    store_create_sql();

    // must build table sepparately so new
    // sql can be properly registered
    build_table();
}

DBEvent::~DBEvent() {
}


void DBEvent::store_add_row_sql() {

    sql_template =  "SELECT name ";
    sql_template += "FROM   sqlite_master ";
    sql_template += "WHERE";
    sql_template += "    type = \"table\"";
    sql_template += ";";

}


void DBEvent::store_create_sql() {

    //std::cerr << "calling store_create_sql from DBEvent\n";

    sql_create =  "CREATE TABLE ";
    sql_create += table_name;
    sql_create += " ( ";
    sql_create += "  hiveId INT PRIMARY KEY NOT NULL, ";
    sql_create += "  entryExitPeak TEXT NOT NULL, ";
    sql_create += "  time LONG LONG NOT NULL ";
    sql_create += " );";

}


bool DBEvent::add_row(int id, std::string eep,
                        long long time ) {
    int   retCode = 0;
    char *zErrMsg = 0;

    char  tempval[128];

    sql_add_row  = "INSERT INTO ";
    sql_add_row += table_name;
    sql_add_row += " ( hiveId, entryExitPeak, time ) ";
    sql_add_row += "VALUES (";

    sprintf (tempval, "%d", id);
    sql_add_row += tempval;
    sql_add_row += ", ";

    sql_add_row += "\"";
    sql_add_row += std::string(eep);
    sql_add_row += "\", ";

    sprintf (tempval, "%llu", time);
    sql_add_row += tempval;

    sql_add_row += " );";

    //std::cout << sql_add_row << std::endl;

    retCode = sqlite3_exec(curr_db->db_ref(),
                           sql_add_row.c_str(),
                           cb_add_rowEvent,
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


bool DBEvent::select_all() {
    //reason we do this is so that our old queries of this DB object are eliminated before recording this query.
    list->clear();
    int   retCode = 0;
    char *zErrMsg = 0;

    sql_select_all  = "SELECT * FROM ";
    sql_select_all += table_name;
    sql_select_all += ";";

    retCode = sqlite3_exec(curr_db->db_ref(),
                           sql_select_all.c_str(),
                           cb_select_allEvent,
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


int cb_add_rowEvent(void  *data,
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

    DBEvent *obj = (DBEvent*) data;

    return 0;
}


int cb_select_allEvent(void  *data,
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

    DBEvent* obj = (DBEvent *) data;

    //create a container of hive objects out of this

    if(obj->list != nullptr) {
        obj->list->add_event(argc, argv, azColName);
   }

    return 0;
}
