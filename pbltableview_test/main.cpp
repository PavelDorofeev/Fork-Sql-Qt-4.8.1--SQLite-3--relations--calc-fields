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

    if ( sqlite.tables().isEmpty())
    {
        QMessageBox::critical( 0 ,
                               mySql::error_,
                               QObject::tr("database is empty?\n %1:\n %2,\n error: %3").arg(sqlite.databaseName()).arg(sqlite.databaseName().arg(sqlite.lastError().text())));

        return 0;
    }

    qWarning()  << "sqlite.driverName() "<< sqlite.driverName();
    qWarning()  << "sqlite.databaseName() "<< sqlite.databaseName();
    qWarning()  << "sqlite.isOpen() "<< sqlite.isOpen();
    qWarning()  << "sqlite.connectionName() "<< sqlite.connectionName();
    qDebug() << " tables " << sqlite.tables();
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
        QMessageBox::critical(0, mySql::error_, str + "\n"+ query.lastError().text());

        return false;
    }
    else
        qDebug() << str;

    return true;
}

/*QSqlQuery query;

QString tableName="goods";

QString sCreateTable = "CREATE TABLE "+tableName+" (id integer primary key autoincrement,productName varchar(100),price double default 0)";

if( ! query.exec(sCreateTable))
{
    qCritical() << "Не удается создать таблицу базы данных : "<< sCreateTable << query.lastError().text();

    return 0;
}
else
    qWarning() << "succefully created table " ;


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
