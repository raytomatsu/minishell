#ifndef DBEvent_H
#define DBEvent_H


#include <iostream>
#include <string>
#include <sqlite3.h>

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../ControlPackage/eventcontainer.h"

#include "dbtool.h"
#include "dbtable.h"

class EventContainer;

class DBEvent: public DBTable
 {
        protected:

            std::string sql_select_all;

        public:

            EventContainer *list;

            DBEvent();
            DBEvent(DBTool     *db,
                      std::string name);

            ~DBEvent();

            void set_list(EventContainer *_list) { list = _list; }

            // An overloaded method to generate a new
            // create command for your child class.
            void store_create_sql();

            // An overloaded method to generate a new
            // insert command for your child class.
            virtual void store_add_row_sql();

            bool add_row(int id, std::string eep,
                         long long time);

            bool select_all();

};

// This is a callback function that is sent to the library and used
// to parse the sql request being sent to the database.
int cb_add_rowEvent(void  *data,
               int    argc,
               char **argv,
               char **azColName);


// This is a callback function that is sent to the library and used
// to parse the sql request being sent to the database.
int cb_select_allEvent(void  *data,
                  int    argc,
                  char **argv,
                  char **azColName);

#endif // DBEvent_H
