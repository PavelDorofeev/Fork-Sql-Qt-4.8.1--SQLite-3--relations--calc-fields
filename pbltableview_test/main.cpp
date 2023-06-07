#include <QtGui/QApplication>
#include "dialog_test.h"
#include <QDebug>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTextCodec>
#include <QDesktopServices>
#include <QStyleFactory>
#include <QDir>
#include "pbltableview/some_tests.h"

#include <QObject>
#include <QToolTip>
#include <QPalette>
#include "logging_system/logging_system.h"
#include "pbltableview/pblapplication.h"
#include <QIcon>

#include "pbltableview/my_sql.h"
#include "pbltableview/pbltableview.h"

bool firstInsertInto(const QString &tbl , const QString &nameCol , const QString &nameVal);

bool createTables();

void setStyle( PblApplication &app );

//(*func()){ return 0};
///int (*)(int);


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
                               "Hello!",
                               QObject::tr("Database is empty"),
                               QObject::tr("Creating new database!")
                               );

        if( ! createTables())
            return 0;

    }

    qWarning()  << "sqlite.driverName() "<< sqlite.driverName();
    qWarning()  << "sqlite.databaseName() "<< sqlite.databaseName();
    qWarning()  << "sqlite.isOpen() "<< sqlite.isOpen();
    qWarning()  << "sqlite.connectionName() "<< sqlite.connectionName();

    // qDebug() << " sizeOf" << sizeof(QSqlDatabase::database()); = 4

    app.slot_change_language("en");

    int res = 1;

    while( res == 1 )
    {
        setStyle( app );

        DialogTest *w = new DialogTest(app.langId , sqlite);

        QObject::connect(w, SIGNAL(sig_changeLanguage(QString)),
                         (PblApplication*)(&app), SLOT(slot_change_language(QString)));

        w->showFullScreen();

        res = w->exec();

        delete w;
    }

    return 0;

}

void setStyle( PblApplication &app )
{
    //--------------------------------------------------------------------

    QSettings sett( DialogTest::progName , DialogTest::fontDir );

    if(sett.contains( "font" ))
    {
        QString ff = sett.value("font").toString();

        qDebug() << "   reestr->value(font) : " << ff;

        QFont font=QFont(ff);

        qDebug() << "       pointSize: " << sett.value("pointSize");
        qDebug() << "       pointSize: " << sett.value("/font/pointSize");

        if( sett.contains("pointSize") && sett.value("pointSize").toInt() > 6)
            font.setPointSize( sett.value("pointSize").toInt());

        if( sett.contains("pointSizeF") && sett.value( "pointSizeF").toReal() > 6)
            font.setPointSizeF(sett.value("pointSizeF").toReal());

        if(sett.contains("pixelSize"))
        {
            int pixelSize = sett.value("pixelSize").toInt();

            if(pixelSize >0)
                font.setPixelSize(pixelSize);
        }

        if ( sett.contains("weight"))
            font.setWeight( sett.value("weight").toInt());

        if( sett.contains("bold"))
            font.setBold( sett.value("bold").toBool());

        if(sett.contains("italic"))
            font.setItalic( sett.value("italic").toBool());

        if(sett.contains("family"))
            font.setFamily(sett.value("family").toString());

        int ps = font.pointSize();

        QApplication::setFont(font);
    }

    // --------------------------------------------------------------

    //QWidget::setWindowTitle()
//    QPalette  pal = QApplication::palette();
//    pal.setColor(QPalette::AlternateBase , QColor(Qt::green));
//    pal.setColor(QPalette::AlternateBase , QColor(Qt::green));
//    QApplication::setPalette(pal);
    //QApplication::setStyle(QStyleFactory::create("Fusion"));

    //QApplication::setStyle(sty);

    QFont font = QApplication::font();

    QFontMetrics fm(font);

    int ww = fm.width('w');
    int hh = fm.height();

    QString em1H = QString::number(hh);

    QString em1 = QString::number(ww);
    QString em2 = QString::number(ww*2);

    QString em05 = QString::number( floor(hh*0.5));
    QString em02 = QString::number( floor(hh*0.2));

    PblTableView::margin_hor = ww;

    QString st = "\n"\

            "QPushButton{\n"\
            "   padding:"+em05+"px;\n"\
            "   margin:"+em05+"px "+em02+"px;\n"\
            "   background-color: white;\n"\
            "   color: green;\n"\
            "   border-radius:"+em02+"px;\n"\
            "}\n"\

            "QPushButton:!enabled{\n"\
            "   background:gray; \n"\
            "   color:white; \n"\
            "}\n"\


            "QToolTip{\n"\
            "   font-size:42px;\n"\
            "   padding:"+em1+"px;\n"\
            "}\n"
/*

                    "QComboBox{\n"\
                    "}\n"\

           "   color: #333;\n"\
                            "padding:"+em1+"px;\n"\
            "QLineEdit{\n"\
            "   padding:"+em1+"px "+em1+"px "+em1+"px "+em1+"px;\n"\
            "}\n"\

            "QTableView{\n"\
            "}\n"\

        */
            "QTableView::item{\n"\
            "padding:"+em05+"px;\n"\
            "}\n"\


            "QHeaderView#vert::section {\n"\
            "   color: #333;\n"\
            "   padding:"+em1+"px "+em1+"px;\n"\
            "   border: 1px solid #f6f7fa;\n"\
            "}\n"\

            "QHeaderView#hor::section {\n"\
            "   color: blue;\n"\
            "   padding:"+em1+"px "+em1+"px;\n"\
            "   border: 1px solid #f6f7fa;\n"\
            "}\n"\


            "QCheckBox{\n"\
            "   spacing: 5px;\n"\
            "   font-size:"+em1H+"px;\n"\
            "}\n"\

            "QCheckBox::indicator {\n"\
            "   width: "+em1H+"px;\n"\
            "   height: "+em1H+"px;\n"\
            "}\n"\

            "QCheckBox::indicator:checked{\n"\
            "   image:url(:icon/img/checked.png);\n"\
            "}\n"\

            ;


    /*



    "background-color: #EEE;\n"\

                "QToolButton{"\
                "width: "+sToolBtnSz+"px;\n"\
                "height: "+sToolBtnSz+"px;\n"\
                "}"\

     QCheckBox {
         spacing: 5px;
     }

     QCheckBox::indicator {
         width: 13px;
         height: 13px;
     }

     QCheckBox::indicator:unchecked {
         image: url(:/images/checkbox_unchecked.png);
     }

     QCheckBox::indicator:unchecked:hover {
         image: url(:/images/checkbox_unchecked_hover.png);
     }

     QCheckBox::indicator:unchecked:pressed {
         image: url(:/images/checkbox_unchecked_pressed.png);
     }

     QCheckBox::indicator:checked {
         image: url(:/images/checkbox_checked.png);
     }

     QCheckBox::indicator:checked:hover {
         image: url(:/images/checkbox_checked_hover.png);
     }

     QCheckBox::indicator:checked:pressed {
         image: url(:/images/checkbox_checked_pressed.png);
     }

     QCheckBox::indicator:indeterminate:hover {
         image: url(:/images/checkbox_indeterminate_hover.png);
     }

     QCheckBox::indicator:indeterminate:pressed {
         image: url(:/images/checkbox_indeterminate_pressed.png);
     }
    0
                */
    qDebug() << st;

    app.setStyleSheet(st);

    QToolTip::setFont(font);
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
                     "sub	INTEGER DEFAULT NULL,"\
                     "qty	double DEFAULT NULL,"\
                     "sum	double DEFAULT NULL,"\
                     "date_ INTEGER DEFAULT NULL," \
                     "PRIMARY KEY(id AUTOINCREMENT))"))
        return false;

    firstInsertInto(tableName , "productName,sum" , "1, 123");


    tableName = "goods";

    if( ! createTbl( tableName,
                     "CREATE TABLE "+tableName+"" \
                     "(id	INTEGER UNIQUE, " \
                     "productName	VARCHAR," \
                     "price	REAL DEFAULT NULL," \
                     "sub_on INTEGER DEFAULT NULL," \
                     " PRIMARY KEY(id AUTOINCREMENT)"\
                     ")"))
        return false;

    firstInsertInto(tableName , "productName,price,sub_on" , "'mango', 123.45 , 1");
    firstInsertInto(tableName , "productName,price,sub_on" , "'apple', 234.56 , 1");
    firstInsertInto(tableName , "productName,price" , "'banana', 345.67");


    tableName = "purchases";


    if( ! createTbl( tableName, "CREATE TABLE "+tableName+" "\
                     "(id INTEGER UNIQUE,"\
                     "productName varchar(100),"\
                     "sub INTEGER DEFAULT NULL,"\
                     "price double default NULL,"\
                     "qty double default NULL,"\
                     "sum double default NULL,"\
                     "cmb	INTEGER DEFAULT -1,"\
                     "chk	INTEGER DEFAULT NULL,"\
                     "foo	INTEGER DEFAULT NULL,"\
                     "PRIMARY KEY(id AUTOINCREMENT)"\
                     ")"))
        return false;


    firstInsertInto(tableName , "productName,price,qty,sum,cmb" , "1, 123.4, 1.35, 166.59 ,0");
    firstInsertInto(tableName , "productName,price,qty,sum,cmb" , "2, 2.5, 2.334 ,5.835, 1");
    firstInsertInto(tableName , "productName,price,qty,sum,chk" , "3, 345.6, 3.4, 1175.04, 1");


    tableName = "sub_accounting";


    if( ! createTbl( tableName, "CREATE TABLE "+tableName+" "\
                     "(id INTEGER UNIQUE,"\
                     "goods_id NOT NULL,"\
                     "val varchar NOT NULL,"\
                     "PRIMARY KEY(id AUTOINCREMENT)"\
                     ")"))
        return false;

    firstInsertInto(tableName , "goods_id,val" , "1, 'XXL'");
    firstInsertInto(tableName , "goods_id,val" , "1, 'XL'");
    firstInsertInto(tableName , "goods_id,val" , "1, 'L'");
    firstInsertInto(tableName , "goods_id,val" , "2, 'M'");
    firstInsertInto(tableName , "goods_id,val" , "2, 'L'");
    firstInsertInto(tableName , "goods_id,val" , "2, 'XX'");


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
