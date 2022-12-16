#include "my_sql.h"
#include <QObject>

const QString mySql::error = QObject::tr("error");
const QString mySql::warning = QObject::tr("warning");

const QString mySql::submitAllFalse = QObject::tr("submitAll returns false,\n table :  '%1',\n error: %2");

const QString mySql::submitFalse = QObject::tr("submit returns false,\n table :  '%1',\n error: %2");


mySql::mySql()
{
}
