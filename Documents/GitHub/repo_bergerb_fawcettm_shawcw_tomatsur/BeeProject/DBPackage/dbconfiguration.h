#ifndef DBCONFIGURATION_H
#define DBCONFIGURATION_H


#include <iostream>
#include <string>
#include <sqlite3.h>

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../ControlPackage/hivecontainer.h"

#include "dbtool.h"
#include "dbtable.h"

class HiveContainer;

class DBConfiguration: public DBTable
 {
        protected:

            std::string sql_select_all;
            std::string sql_select_max;
            std::string sql_select_tsl;

        public:

            HiveContainer *list;
            int maxHiveId;
            int counter;

            DBConfiguration();
            DBConfiguration(DBTool     *db,
                      std::string name);

            ~DBConfiguration();

            void set_list(HiveContainer *_list) { list = _list; }
            void set_maxHiveId(int _id) {maxHiveId = _id; }

            // An overloaded method to generate a new
            // create command for your child class.
            void store_create_sql();

            // An overloaded method to generate a new
            // insert command for your child class.
            virtual void store_add_row_sql();

            bool add_row(int id, int temperature,
                         std::string season,
                         std::string location);

            bool select_all();

            bool select_all_from_hiveID(int hiveID);

            bool select_all_from_temperature_season(int temp, std::string season);

            bool select_max_hiveId();

            bool is_it_empty();
};

// This is a callback function that is sent to the library and used
// to parse the sql request being sent to the database.
int cb_add_row(void  *data,
               int    argc,
               char **argv,
               char **azColName);


// This is a callback function that is sent to the library and used
// to parse the sql request being sent to the database.
int cb_select_all(void  *data,
                  int    argc,
                  char **argv,
                  char **azColName);

// This is a callback function that is sent to the library and used
// to parse the sql request being sent to the database.
int cb_select_max(void  *data,
                  int    argc,
                  char **argv,
                  char **azColName);

int cb_is_it_empty(void  *data,
                  int    argc,
                  char **argv,
                  char **azColName);

#endif // DBCONFIGURATION_H
