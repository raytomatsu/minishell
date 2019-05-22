#ifndef DBCONNECTOR_H
#define DBCONNECTOR_H

#include "../DBPackage/dbtool.h"
#include "../DBPackage/dbtable.h"
#include "../DBPackage/dbhive.h"
#include "../DBPackage/dbconfiguration.h"


class DBConnector
{
public:
    DBConnector();

private:
    DBTool *dbtool;
    DBHive *ext;
    DBConfiguration *exC;
};

#endif // DBCONNECTOR_H
