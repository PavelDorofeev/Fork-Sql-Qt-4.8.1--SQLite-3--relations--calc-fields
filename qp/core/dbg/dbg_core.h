#ifndef QP_DBG_CORE_H
#define QP_DBG_CORE_H

#include <QString>

#include <QEvent>
#include <QDebug>
#include <QProcess>
#include <QEvent>
#include <QFile>
#include <QObject>

#include "qp/core/dll_qp_core_global.h"

namespace qp
{

/*
  static when used in a function at namespace level means internal linkage.
*/

class LIB_PREFIX_QP_CORE dbg_core
{
public:
    dbg_core();

    static const QString toStr_File_Permissions(QFile::Permissions prm);

    static const QString toStr_ProcessError(QProcess::ProcessError err);

    static const QString toStr_ProcessExitStatus(QProcess::ExitStatus status);




    static const QString toStr_Event_Type(QEvent::Type event);

    static const QString toStr_ItemFlag(int ItemFlag);

    static const QString toStr_InputMethodQuery(Qt::InputMethodQuery mtd);


    static const QString  toStr_modelRole(int role);

    static const QString toStr_KeyboardModifier(Qt::KeyboardModifiers mdf);


    static  const QString error_;// = QString::fromUtf8("error");
    static  const QString warning;// = QString::fromUtf8("warning");

    static const QString meta_info(QObject * obj);
};
}


#endif // QP_DBG_H
