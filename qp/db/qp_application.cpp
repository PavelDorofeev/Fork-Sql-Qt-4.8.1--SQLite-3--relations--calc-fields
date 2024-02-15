#include "qp_application.h"
#include <QMessageBox>
#include <QDebug>
#include <QEvent>
#include "qp/dbg/dbg.h"

QpApplication::QpApplication(int &argc, char **argvs, int flags) :
    QApplication(argc, argvs, flags),
    langId(QString())
{


}

bool QpApplication::notify(QObject *obj, QEvent *evt)
{
    //qWarning()<< "PblApplication::notify" << obj << evt<< dbg::toStr_Event_Type( evt->type() );

    bool bb= QApplication::notify( obj, evt);

    //qWarning()<< "  ret" << bb;

    return bb;

}

bool QpApplication::slot_change_language(QString name)
{

    if( qtLanguageTranslator.load(QString("QtLangPblTableView_") + name))
    {
        /*QMessageBox::critical(0,
                              qp::dbg::error_ ,
                              QObject::tr("loading language '%1' succesfull").arg(name));*/
        langId = name;
    }
    else
    {
        QMessageBox::critical(0,
                           qp::dbg::error_ ,
                           QObject::tr("loading language '%1' unsuccesfull").arg(name));
        langId = name;
        //return false;
    }

    installTranslator(&qtLanguageTranslator);



    return true;

}
