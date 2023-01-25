#include <QtGui/QApplication>
#include "dialog.h"
#include <QDebug>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTextCodec>
#include <QDesktopServices>
#include <QDir>
#include "pbltableview/some_tests.h"
#include <QObject>

#include "logging_system/logging_system.h"
#include "pbltableview/pblapplication.h"
#include <QIcon>
#include "pbltableview/my_sql.h"

bool firstInsertInto(const QString &tbl , const QString &nameCol , const QString &nameVal);
bool createTables();

int main(int argc, char *argv[])
{
    PblApplication app(argc, argv);

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    // -----------------------------------------------------------------
    //                      logging_System
    // -----------------------------------------------------------------

    logging_System::LOG_TYPES logTypes = (logging_System::LOG_WARNING
                                          |logging_System::LOG_CRITICAL
                                          |logging_System::LOG_FATAL);

    bool logging_history_ON = true;
    logTypes |= logging_System::LOG_DEBUG; // не подсвечивается , но работает
    logging_history_ON = false;

    qDebug() << "QDir::currentPath()" << QDir::currentPath();

    bool ll = logging_System::init(
                QDir::currentPath(),
                logging_System::LOG_FILE_NAME,
                logTypes,
                false,
                logging_history_ON );

    qInstallMsgHandler(logging_System::logCatcher);

    QSqlDatabase sqlite;

    sqlite = QSqlDatabase::addDatabase("QSQLITE");

    if(sqlite.lastError().type() != QSqlError::NoError)
    {
        QMessageBox::critical( 0 , mySql::error_,  QObject::tr("addDatabase returns false:\n error: %1").arg(sqlite.lastError().text()));
        return 0;
    }

    sqlite.setDatabaseName(QDir::currentPath()+"/test.db");

    qDebug() << QDir::currentPath()+"/test.db";

    //sqlite.setDatabaseName(":memory:");

    if (! sqlite.open())
    {
        QMessageBox::critical( 0 , mySql::error_,  QObject::tr("database file is not opened:\n %1,\n error: %2").arg(sqlite.databaseName().arg(sqlite.lastError().text())));

        return 0;
    }

    qDebug() << " tables " << sqlite.tables();

    if ( sqlite.tables().count() == 0
         || ( sqlite.tables().count()==1  && sqlite.tables().at(0) == "sqlite_sequence") )
    {
        QMessageBox::critical( 0 ,
                               mySql::error_,
                               QObject::tr("database is empty?\n\n %1:\n\n error: %3").
                               arg(sqlite.databaseName()).
                               arg(sqlite.lastError().text()));

        if( ! createTables())
            return 0;

    }

    qWarning()  << "sqlite.driverName() "<< sqlite.driverName();
    qWarning()  << "sqlite.databaseName() "<< sqlite.databaseName();
    qWarning()  << "sqlite.isOpen() "<< sqlite.isOpen();
    qWarning()  << "sqlite.connectionName() "<< sqlite.connectionName();

    // qDebug() << " sizeOf" << sizeof(QSqlDatabase::database()); = 4


    QString st = "QTableView{\n"\
            "border: 2px solid #3873d9;\n"\
            "/*padding: 35px;*/\n"\
            "/*background-color: yellow;*/\n"\
            "/*selection-background-color: green;*/\n"\
            "}\n"\
            "QTableView::item{\n"\
            "margin: 7px;\n"\
            "}\n"\
            "QHeaderView{\n"\
            "/*margin-right: 25px; влияет отображение строк снизу*/\n"\
            "/*padding: 0px; влияет отображение строк снизу*/\n"\
            "}\n"\
            "QHeaderView::section{\n"\
            "/*color: blue;*/\n"\
            "/*background-color: #DDD;*/\n"\
            "/*text-align:left;*/"\
            "/*margin-left: 15px;*/\n"\
            "/*border: this solid #EEE;*/\n"\
            "}\n";

    //    app.setStyleSheet(st);

    app.slot_change_language("en");

    int res = 1;

    while( res == 1 )
    {
        DialogTest *w = new DialogTest(app.langId , sqlite);

        QObject::connect(w, SIGNAL(sig_changeLanguage(QString)),
                         (PblApplication*)(&app), SLOT(slot_change_language(QString)));

        res = w->exec();

        delete w;
    }

    return 0;

}

bool firstInsertInto(const QString &tbl , const QString &nameCol , const QString &nameVal)
{
    QString str="insert into "+ tbl +" ("+nameCol+") VALUES("+nameVal+");";

    QSqlQuery query;

    if( ! query.exec(str))
    {
        QMessageBox::critical(0,
                              mySql::error_,
                              str + "\n"+ query.lastError().text());

        return false;
    }
    else
        qDebug() << str;

    return true;
}

bool createTbl(const QString &tn, const QString & sCreateTable)
{
    QSqlQuery query;

    if( ! query.exec(sCreateTable))
    {
        QMessageBox::warning(0 ,
                             mySql::error_,
                             QObject::tr("Не удается создать таблицу базы данных %1:\n\n%2 ").
                             arg(tn).
                             arg(query.lastError().text()));

        return false;
    }

    QMessageBox::warning(0 ,
                         "OK:",
                         QObject::tr("succefully created table %1").
                         arg(tn));
    return true;
}

bool createTables()
{
    QString  tableName;

    tableName = "checks";


    if( ! createTbl( tableName, "CREATE TABLE "+tableName+" ("\
                     "id	INTEGER UNIQUE,"\
                     "productName	INTEGER NOT NULL,"\
                     "sum	double DEFAULT 0,"\
                     "date_ INTEGER DEFAULT 0," \
                     "PRIMARY KEY(id AUTOINCREMENT))"))
        return false;

    firstInsertInto(tableName , "productName,sum" , "1, 123");


    tableName = "goods";

    if( ! createTbl( tableName,
                     "CREATE TABLE "+tableName+"" \
                     "(id	INTEGER UNIQUE, " \
                     "productName	VARCHAR," \
                     "price	REAL," \
                     " PRIMARY KEY(id AUTOINCREMENT)"\
                     ")"))
        return false;

    firstInsertInto(tableName , "productName,price" , "'mango', 123.45");
    firstInsertInto(tableName , "productName,price" , "'apple', 234.56");
    firstInsertInto(tableName , "productName,price" , "'banana', 345.67");



    tableName = "purchases";


    if( ! createTbl( tableName, "CREATE TABLE "+tableName+" "\
                     "(id INTEGER UNIQUE,"\
                     "productName varchar(100),"\
                     "price double default 0,"\
                     "qty double default 0,"\
                     "sum double default 0,"\
                     "cmb	INTEGER DEFAULT -1,"\
                     "chk	INTEGER DEFAULT 0,"\
                     "foo	INTEGER DEFAULT 0,"\
                     "PRIMARY KEY(id AUTOINCREMENT)"\
                     ")"))
        return false;


    firstInsertInto(tableName , "productName,price,qty,cmb" , "1, 123.4, 1.3 ,0");
    firstInsertInto(tableName , "productName,price,qty,cmb" , "2, 2.5, 2.334 ,1");
    firstInsertInto(tableName , "productName,price,qty,chk" , "3, 345.6, 3.4, 1");



    return true;

}


/*QSqlQuery query;

QString tableName="goods";




firstInsertInto(tableName , "productName,price" , "1, 123.45");
firstInsertInto(tableName , "productName,price" , "2, 234.56");
firstInsertInto(tableName , "productName,price" , "3, 345.67");

tableName ="purchases";

sCreateTable="CREATE TABLE "+tableName+" "\
        "(id integer primary key autoincrement,productName_id int default 0,price double default 0,qty double default 1,sum double default 0)";

if( ! query.exec(sCreateTable))
{
    qCritical() << "Не удается создать таблицу базы данных : "<< sCreateTable << query.lastError().text();

    return 0;
}
else
    qWarning() << "succefully created table " ;

firstInsertInto(tableName , "productName_id,price,qty,sum" , "1, 123.45, 1, 123.45");
firstInsertInto(tableName , "productName_id,price,qty,sum" , "2, 123.45, 1, 123.45");
firstInsertInto(tableName , "productName_id,price,qty,sum" , "3, 123.45, 1, 123.45");
*/
