#include "logging_system.h"
#include <QDesktopServices>

#include <QDateTime>
#include <QDir>
#include <QDebug>
#include <QFile>
//#include "my_gui/my_gui.h"
#include <io.h>
#include <stdio.h>
#include <QUrl>
#include <iostream>

/* Необходима инициализация статических переменных */

logging_System * logging_System::static_instance = NULL;
//DLL_MY_LIB_EXPORT QString logging_System::dirName_=0;
//DLL_MY_LIB_EXPORT QString logging_System::fileName_=0;
//DLL_MY_LIB_EXPORT bool logging_System::toStdOut_ = false;

/* ------------------------- add just its to main.c-----------------------------

    static logging_System *logSystem = logging_System::pStatic_instance(                            QDesktopServices::storageLocation(QDesktopServices::DataLocation)+"\\"+PROG_DATA_DIR,
                                                                "log.txt" ,
                                                               logging_System::LOG_TYPES(logging_System::LOG_DEBUG
                                                                                         |logging_System::LOG_WARNING) ,
                                                                false  );

    qInstallMsgHandler(logCatcher);


----------------------------------------------------------*/

// при первом вызове qDebug вызовется конструктор logging_System!

#include <cstdio>

const QString logging_System::LOGS_DIR              = "log";
const QString logging_System::LOGS_HYSTORY_DIR      = "logs";
const QString logging_System::LOG_FILE_NAME         = "log.txt";

logging_System::logging_System(QString &dirName_,
                               QString &fileName_,
                               LOG_TYPES types,
                               bool toStdOut,
                               bool history_ON_,
                               QObject *parent) :
    QObject(parent),
    stdOutNotifier(NULL),
    debug_Enabled(false),
    warning_Enabled(false),
    critical_Enabled(true),
    fatal_Enabled(true)
{

    history_ON = history_ON_;

    if(types & LOG_DEBUG)
        debug_Enabled = true;

    if(types & LOG_WARNING)
        warning_Enabled = true;

    /* if(types & LOG_CRITICAL)
        critical_Enabled = true;

    if(types & LOG_FATAL)
        fatal_Enabled = true;*/

    dirName=dirName_;
    fileName=fileName_;

    qDebug() << " logging : "<< dirName << fileName;

    if( ! toStdOut)
    {
        toStdOut_ = toStdOut;

        if(! QDir(dirName).exists())
        {
            if( ! QDir().mkdir(dirName))
            {
                qCritical()  << "can't create folder  (for log file) :  " << dirName;

                return ;
            }

            qWarning()  << "create folder (for log file) :  " << dirName;
        }

        if(! QDir(dirName+"\\"+LOGS_HYSTORY_DIR).exists())
        {
            if( ! QDir().mkdir(dirName +"\\"+LOGS_HYSTORY_DIR))
            {
                qCritical()  << "can't create folder  (for log file) :  " << dirName+"\\"+LOGS_HYSTORY_DIR;
                return ;
            }
            qWarning()  << "create folder  (for old log files) :  " << dirName+"\\"+LOGS_HYSTORY_DIR;
        }

        logFilePath = dirName + "\\"+fileName;

        qDebug() << " logFilePath : " << logFilePath;

        m_logFile_.setFileName(logFilePath);
        //m_logFile_.setPermissions()


        if( ! testLargeFileAndSave(logFilePath) )
            ;

        if( ! m_logFile_.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Unbuffered))
        {
            /* myGui::message(0,
                        QObject::tr("Сбой запуска программы"),
                        QObject::tr("К сожалению не удается создать лог файл  : ")+logFilePath);*/

            qCritical()  << "can't open log file :  " << logFilePath;
            return ;
        }

        FILE *loggingStreamStdout;
        FILE *loggingStreamStderr;
        //QFile loggingFile("app.log");

        //loggingFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Unbuffered);
        int fd = m_logFile_.handle();

        freopen_s ( &loggingStreamStdout, "\\\\.\\NUL", "w", stdout);
        setvbuf ( loggingStreamStdout, NULL, _IONBF, 0);

        freopen_s (&loggingStreamStderr, "\\\\.\\NUL", "w", stderr);
        setvbuf ( loggingStreamStderr, NULL, _IONBF, 0);

        _dup2 (fd, _fileno(stdout));
        _dup2 (fd, _fileno(stderr));

        //freopen(m_logFile_.fileName().toLocal8Bit().data(), "w", stdout); // в начало stdout потом qDebug()


    }

    /*   old_stdout = _dup( 1 );   // "old" now refers to "stdout"
    // Note:  file descriptor 1 == "stdout"
    if( old_stdout == -1 )
    {
        perror( "_dup( 1 ) failure" );
        exit( 1 );
    }

    _write( old_stdout, "This goes to stdout first\n", 26 );

    if( fopen_s( &stdOutFile, "data", "w" ) != 0 )
    {
        puts( "Can't open file 'data'\n" );
        exit( 1 );
    }

    stream = new QTextStream(stdOutFile ,QIODevice::WriteOnly|QIODevice::ReadOnly);

    //stream << QString("sdfasfadsfadsfadsfads");

    // stdout now refers to file "data"
    if( -1 == _dup2( _fileno( stdOutFile ), 1 ) )
    {
        perror( "Can't _dup2 stdout" );
        exit( 1 );
    }
    puts( "This goes to file 'data'\n" );

    // Flush stdout stream buffer so it goes to correct file
    fflush( stdout );
    fclose( stdOutFile );

    // Restore original stdout
    _dup2( old_stdout, 1 );
    puts( "This goes to stdout\n" );
    puts( "The file 'data' contains:" );
    _flushall();
    system( "type data" );*/

}


logging_System * logging_System::pStatic_instance(QString dirName,
                                                  QString fileName,
                                                  LOG_TYPES debug,
                                                  bool stdOut,
                                                  bool history_ON)
{
    if( logging_System::static_instance == NULL)
        logging_System::static_instance = new logging_System(dirName ,
                                                             fileName,
                                                             debug,
                                                             stdOut,
                                                             history_ON);

    return logging_System::static_instance;
}

void logging_System::logCatcher(QtMsgType type, const char *msg)
{
    //out << QDateTime::currentDateTime().toString("hh:mm:ss ");

    //if(m_logFile_ == 0)    return;

    //if(! m_logFile_.isOpen())   return;

    if( logging_System::static_instance !=NULL)
        logging_System::static_instance->loggerMaster(type , msg);

}

void logging_System::loggerMaster(QtMsgType type,const QString & msg)
{
    /*static QTextStream cout(stdout);
    static QTextStream cerr(stderr);*/
    //qDebug() << "logging_System::loggerMaster";

    QString format="hh:mm:ss zzz";

    switch (type)
    {
    case QtDebugMsg:

        if( debug_Enabled )
        {
            if(toStdOut_)
            {
                std::cout << QDateTime::currentDateTime().toString(format).toLocal8Bit().constData() << std::flush;
                std::cout << QString(" Debug: ").toUtf8().constData() << std::flush;
                std::cout << QString(msg+'\n').toUtf8().constData() << std::flush;
            }
            else
            {
                m_logFile_.write(QDateTime::currentDateTime().toString(format).toUtf8());
                if(msg != "\n" && msg != "\n\n")
                    m_logFile_.write(QString(" Debug: ").toUtf8());

                m_logFile_.write( QString(msg).toUtf8() +"\n");
                m_logFile_.flush();
            }
        }

        break;

    case QtWarningMsg:

        if( warning_Enabled )
        {
            if(toStdOut_)
            {
                std::cout <<QDateTime::currentDateTime().toString("hh:mm:ss ").toUtf8().constData() << std::flush;
                std::cout << QString("Warning: "+ QString(msg)+"\n").toUtf8().constData() << std::flush;
            }
            else
            {
                m_logFile_.write(QDateTime::currentDateTime().toString("hh:mm:ss ").toUtf8());
                m_logFile_.write("Warning: "+ QString(msg).toUtf8()+"\n");
                m_logFile_.flush();
            }
        }
        break;

    case QtCriticalMsg: // = QtSystemMsg

        if(critical_Enabled)
        {
            if(toStdOut_)
            {
                std::cout <<QDateTime::currentDateTime().toString("hh:mm:ss ").toUtf8().constData() << std::flush;
                std::cout << QString("\n---------------- Critical: --------------------\n").toUtf8().constData() << std::flush;
                std::cout << QString(msg).toUtf8().constData() << std::flush;
                std::cout << QString("\n---------------- Critical: --------------------\n").toUtf8().constData()<< std::flush;
            }
            else
            {
                m_logFile_.write(QDateTime::currentDateTime().toString("hh:mm:ss ").toUtf8());
                m_logFile_.write(QString("\n---------------- Critical: --------------------\n").toUtf8());
                m_logFile_.write("Critical: "+ QString(msg).toUtf8());
                m_logFile_.write(QString("\n---------------- Critical: --------------------\n").toUtf8());
                m_logFile_.flush();
            }
        }
        break;

    case QtFatalMsg:

        if(fatal_Enabled)
        {
            if(toStdOut_)
            {
                std::cout << QString("---------------- Critical: --------------------\n").toUtf8().constData()<< std::flush;
                std::cout << QString("Fatal: "+ msg).toUtf8().constData();
                std::cout << QString("---------------- Critical: --------------------\n").toUtf8().constData()<< std::flush;
            }
            else
            {

                m_logFile_.write(QString("---------------- Critical: --------------------\n").toUtf8());
                m_logFile_.write("Fatal: "+ QString(msg).toUtf8());
                m_logFile_.write(QString("---------------- Critical: --------------------\n").toUtf8());
                m_logFile_.flush();
            }
        }

        abort();
        break;
    }
}


void logging_System::stdOutDataAvailable(int ii)
{
    qDebug() << "stdOutDataAvailable : " << ii;

}


bool logging_System::init()
{
    if ( ! initLoggingFiles())
        return false;

    if ( ! initLoggingSystem())
        return false;



    return true;
}

bool logging_System::initLoggingFiles()
{
    if(! m_logFile_.isOpen())
        return false;

    return true;
}

bool logging_System::initLoggingSystem()
{
    return true;
}

bool logging_System::testLargeFileAndSave(QString &logFilePath)
{
    bool res = false;

    QFile file(logFilePath);

    if( ! file.exists())
        return true;


    if( ! history_ON)
    {
        if( ! file.open(QFile::WriteOnly )) // QFile::Text |QFile::Text |QFile::Truncate))
        {
            return false;
        }

        file.resize(0); // clear !!!
        file.flush();
        file.close();

        return true;
    }

    qint64 sz = file.size();

    if( sz > 100000)
    {
       // QDir toDir(dirName);

        QString fn = QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss")+".txt";

        //qDebug() << " dirName " << dirName<< " LOG_FILE_NAME : " << LOG_FILE_NAME << " LOGS_HYSTORY_DIR "<<LOGS_HYSTORY_DIR;

        QString to = dirName+"\\"+ LOGS_HYSTORY_DIR+"\\log-" + fn;
        qDebug() << " to : " << to;
        res = file.rename(to);

        return res;
    }
    else
        return true;
}

bool logging_System::slot_openLoggingOnToOnNotepad()
{
    if ( ! QDesktopServices::openUrl(QUrl::fromLocalFile(logFilePath)))
    {
        qCritical() << "ERROR OPEN  logFilePath : " << logFilePath;
        return false;
    }


    return true;
}
