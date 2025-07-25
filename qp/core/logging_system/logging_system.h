#ifndef LOGGING_SYSTEM_H
#define LOGGING_SYSTEM_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QFile>
#include <QVariant>
#include <QIODevice>
#include <QSettings>
//#include <QComboBox>
//#include <QStandardItemModel>
//#include <QListWidget>

#include <QTextStream>

//void myMessageOutput(QtMsgType type, const char *msg);

#include "../dll_qp_core_global.h"

class LIB_PREFIX_QP_CORE logging_System
{

public:

    enum LOG_TYPE{
        LOG_WARNING=1,
        LOG_CRITICAL=2,
        LOG_FATAL=4,
        LOG_DEBUG=8,
        LOG_ALL=LOG_WARNING|LOG_CRITICAL|LOG_FATAL|LOG_DEBUG
    };
    Q_DECLARE_FLAGS(LOG_TYPES, LOG_TYPE)

    static const QString LOGS_DIR;

    static const QString LOGS_HYSTORY_DIR;

//    static const QString LOG_FILE_NAME;

    explicit logging_System();//QObject *parent = 0 );

    static void setLoggingCommands( int logTypes );

    static void setLoggingToStdOut( bool std_out );

    ~logging_System();

//    static const  QString getLogDir() ;
    static const  QString getLogFile() ;

    static void logCatcher(QtMsgType type, const char *msg);

    static logging_System *logg;

    static bool init(QString dirName,
                     QString fileName,
                     LOG_TYPES debug,
                     bool stdOut,
                     bool history_ON);

    static LOG_TYPES types;

public:

    static void mess(QtMsgType type,const QString &);

    static QString dirName;
//    static QString fileName;
    static bool toStdOut_;

    static QString logFilePath;

    static QObject *parent_;

    bool initLoggingFiles();

    bool initLoggingSystem();

    static QFile *logFile;

    void duplicate(QFile * log_File);

//    static bool openLoggingOnToOnNotepad();

    static bool history_ON;


    int old_stdout;

    FILE *stdOutFile;

    QTextStream *stream;

    static bool debug_Enabled;
    static bool warning_Enabled;
    static bool critical_Enabled;
    static bool fatal_Enabled;

    static bool testLargeFileAndSave(QString  &file);

signals:

    
public slots:
    void stdOutDataAvailable(int);


private:

    
};

#endif // LOGGING_SYSTEM_H
