#include "my_sql.h"
#include <QObject>

#include <QCoreApplication>

const QString mySql::error_ =  QObject::trUtf8("error");

const QString mySql::warning =  QObject::trUtf8("warning");

const QString mySql::submitAllFalse = QObject::trUtf8("submitAll returns false,\n table :  '%1',\n error: %2");

const QString mySql::submitFalse = QObject::trUtf8("submit returns false,\n table : '%1',\n error: %2");


mySql::mySql()
{
}
