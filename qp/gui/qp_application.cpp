#include "qp_application.h"
#include <QMessageBox>
#include <QDebug>
#include <QEvent>
#include "qp/core/dbg/dbg.h"
#include <iostream>
#include <QProcessEnvironment>
#include "qp/core/meta/meta.h"
#include "qp/core/dbg/dbg_core.h"
//#include "localsocket.h"
#include <QDir>

//--------------------------------------------------
// проверка загрузки/инициализации кода
//--------------------------------------------------
int static_init_QpApplication()
{
    qDebug("init QpApplication");
    return 1;
}
static int someArray[] = {static_init_QpApplication()} ;



QpApplication::QpApplication(int &argc, char **argvs, int flags) :
    QApplication(argc, argvs, flags),
    langId(QString())
{

    qp::meta::cnct( this , SIGNAL(aboutToQuit()) ,
                    this, SLOT( about_to_quit()));

    qp::meta::cnct( this , SIGNAL(lastWindowClosed()) ,
                    this, SLOT( slot_lastWindowClosed()));




}

bool QpApplication::notify( QObject *obj, QEvent *evt)
{
    /*
      ПОХОЖЕ ВСЕ СОБЫТИЯ ЗДЕСЬ ПPУТ
      И ОТPИСОВКА И ХЗ ЧТО
    */
    //qDebug()<< "QpApplication::notify" << obj->objectName() << evt<< qp::dbg::toStr_Event_Type( evt->type() );

    if( evt->type() == QEvent::ThreadChange )
    {
//        qWarning() <<"    QEvent::ThreadChange obj->thread()" << obj->thread();
    }

    bool bb= QApplication::notify( obj, evt);

    //int tt =(int) evt->type();

    //qDebug()<< " QpApplication::notify " << evt->type() <<  qp::dbg::toStr_Event_Type( evt->type() );

//    if( tt = QEvent::Quit)
//    {

//    }
    return true;//bb;

}



bool QpApplication::slot_change_language(QString name)
{
    //    int nn =0;
    //    int ii =1/nn;


    qDebug() << "------------------ systemEnvironment -------------------------";
    QString sys;
    foreach (QString pp, QProcessEnvironment::systemEnvironment().toStringList())
    {
        qDebug() << pp;
        sys+=pp+"\n";
    }

    //    qDebug() << "--------------------- environment ----------------------";
    //    QString env;
    //    //QApplication
    //    foreach (QString pp, QProcessEnvironment::environment())
    //    {
    //        qDebug() << pp;
    //        env+=pp+"\n";
    //    }


    QString fullName = QString("QtLangPblTableView_") + name;

    if( qtLanguageTranslator.load( fullName ))
    {
        /*QMessageBox::critical(0,
                              qp::dbg::error_ ,
                              QObject::tr("loading language '%1' succesfull").arg(name));*/
        langId = name;
    }
    else
    {
        QMessageBox::critical(0,
                              qp::dbg_core::error_ ,
                              QObject::tr("loading language '%1' unsuccessful\n"\
                                          "in dir : %2")
                              .arg(fullName+".qm")
                              .arg(QDir::currentPath())
                              );
        langId = name;
        const  char * err = "loading language is unsuccesfull";

        //const  char * err = QString("loading language '%1' unsuccesfull").arg("QtLangPblTableView_"+name).toLocal8Bit();
        //qWarning()<< err.data();
        //qCritical()<<err.data();

        //sprintf(()
        //const  char * application_DirPath = "applicationDirPath: " + applicationDirPath().data();

        // проблема ! только нативный char * работает

        //std::cout << application_DirPath;
        std::cerr << err << std::endl;

        exit(234); // устанавливает result процесса
        return false;

    }

    installTranslator(&qtLanguageTranslator);



    return true;

}


void QpApplication::slot_msg()
{
    qDebug() << "QpApplication::slot_starter_connected()";
}

void QpApplication::slot_lastWindowClosed()
{
    ////LocalSocket::get_ptr()-> writeMsg("QpApplication::slot_lastWindowClosed()");
    qDebug() << "QpApplication::slot_lastWindowClosed()";
}

void QpApplication::about_to_quit()
{
    qDebug() << "QpApplication::aboutToQuit()";

    ////LocalSocket::get_ptr()-> writeMsg("QpApplication::about_to_quit()");

    QCoreApplication::quit();

}
