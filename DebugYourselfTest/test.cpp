#include "pch.h"


#include <type_traits>
#include <string>

//#include <sqlite3.h>

#include <DebugYourself.h>

#include <DebugYourselfUtility.h>
#include <DebugYourselfDatabase.h>


template<class Class>
using ObjectDebug_DebuggedClass = DebugYourself::OVR<Class,
    int,
    bool,
    char>;




TEST(DatabaseDebugging, Schema) {

    using SQLType = DebugYourselfDatabaseTable<>::Types::SQLite;

    DebugYourselfDatabase database;

    DebugYourselfDatabaseTable<SQLType::INTEGER, SQLType::TEXT, SQLType::TEXT> 
        table(&database, "DEBUGYOURSELFTABLE", "COUNT", "TEXT1", "TEXT2");

    table.add(34, "test1", "test2");
    table.add(65, "test3", "test4");

    table.push();

}