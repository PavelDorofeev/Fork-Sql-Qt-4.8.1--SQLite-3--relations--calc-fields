#ifndef QP_DBG1_H
#define QP_DBG1_H

#include <QString>


#include "qp/core/dll_qp_core_global.h"

namespace qp
{
/*
  static when used in a function at namespace level means internal linkage.
*/

class LIB_PREFIX_QP_CORE dbg
{

public:

    dbg();

    static  const QString error_;// = QString::fromUtf8("error");
    static  const QString warning;// = QString::fromUtf8("warning");
    static  const QString submitAllFalse;// = QString::fromUtf8("submitAll returns false,\n table :  '%1',\n error: %2");
    static  const QString submitFalse;// = QString::fromUtf8("submit returns false,\n table : '%1',\n error: %2");

};

}

#endif // QP_DBG_H
