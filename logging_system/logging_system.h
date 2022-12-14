#ifndef LOGGING_SYSTEM_H
#define LOGGING_SYSTEM_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QVariant>
#include <QIODevice>
#include <QSettings>
#include <QComboBox>
#include <QStandardItemModel>
#include <QListWidget>
//#include "my_debug.h"
#include <QFile>
#include <QSocketNotifier>
#include <io.h>
#include <QTextStream>

//void myMessageOutput(QtMsgType type, const char *msg);

#include "common/dll_my_lib_global.h"

//DLL_MY_LIB_EXPORT void logCatcher(QtMsgType type, const char *msg);

class DLL_MY_LIB_EXPORT logging_System : public QObject
{
    Q_OBJECT
public:
    enum LOG_TYPE{
        LOG_WARNING=1,
        LOG_CRITICAL=2,
        LOG_FATAL=4,
        LOG_DEBUG=8
          };
     Q_DECLARE_FLAGS(LOG_TYPES, LOG_TYPE)

    static const QString LOGS_DIR;
    static const QString LOGS_HYSTORY_DIR;
    static const QString LOG_FILE_NAME;

    explicit logging_System(QString &dirName,
                            QString &fileName,
                            LOG_TYPES debug = (LOG_TYPES)(LOG_WARNING|LOG_CRITICAL),
                            bool toStdOut=false,
                            bool history_ON_ = false,
                            QObject *parent = 0
            );



    bool init();

    static void logCatcher(QtMsgType type, const char *msg);

    static logging_System *static_instance;
    static logging_System *pStatic_instance(QString dirName,
                                            QString fileName,
                                            LOG_TYPES debug,
                                            bool stdOut,
                                            bool history_ON);

public:
    void loggerMaster(QtMsgType type,const QString &);

    QString dirName;
    QString fileName;
    bool toStdOut_;

    QString logFilePath;
    static QObject *parent_;
    bool initLoggingFiles();
    bool initLoggingSystem();
    //QFile *m_logFile_;
    //static void myMessageOutput(QtMsgType type, const char *msg);

    QFile m_logFile_;
    QSocketNotifier *stdOutNotifier;
signals:

    
public slots:
    void stdOutDataAvailable(int);
    bool slot_openLoggingOnToOnNotepad();

private:
    int old_stdout;
    bool history_ON;
    FILE *stdOutFile;
    QTextStream *stream;
    bool debug_Enabled;
    bool warning_Enabled;
    bool critical_Enabled;
    bool fatal_Enabled;
    bool testLargeFileAndSave(QString  &file);
    //explicit logging_System();//QString dirName="", QString fileName="", QObject *parent = 0);

    //logging_System(QObject *parent = 0): QObject(parent){}
    
};

#endif // LOGGING_SYSTEM_H
