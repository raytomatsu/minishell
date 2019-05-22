#ifndef DBHIVE_H
#define DBHIVE_H

#include <iostream>
#include <string>
#include <sqlite3.h>

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../ControlPackage/activitycontainer.h"

#include "dbtool.h"
#include "dbtable.h"

class activityContainer;

class DBHive: public DBTable
 {
        protected:

            std::string sql_select_all;

        public:

            activityContainer *list;

            DBHive();
            DBHive(DBTool     *db,
                      std::string name);

            ~DBHive();

            void set_list(activityContainer *_list) {list = _list; }

            // An overloaded method to generate a new
            // create command for your child class.
            void store_create_sql();

            // An overloaded method to generate a new
            // insert command for your child class.
            virtual void store_add_row_sql();

            bool add_row(int,
                         std::string,
                         unsigned long long);

            bool select_all();
};

// This is a callback function that is sent to the library and used
// to parse the sql request being sent to the database.
int cb_add_rowHIVE(void  *data,
               int    argc,
               char **argv,
               char **azColName);


// This is a callback function that is sent to the library and used
// to parse the sql request being sent to the database.
int cb_select_allHIVE(void  *data,
                  int    argc,
                  char **argv,
                  char **azColName);

#endif // DBHIVE_H
