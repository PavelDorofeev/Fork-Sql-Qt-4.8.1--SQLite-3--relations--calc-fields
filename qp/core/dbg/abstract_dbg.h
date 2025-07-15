#ifndef ABSTRACT_DBG_H
#define ABSTRACT_DBG_H

#include <QDebug>
#include <QDateTime>
#include <QMetaType>
#include <QByteArray>
#include <QObject>

#include "qp/core/dll_qp_core_global.h"

class LIB_PREFIX_QP_CORE ADbg
{
public:
    ADbg();

    virtual QString fullInfo() const =0;

    friend LIB_PREFIX_QP_CORE QDebug operator<<(QDebug d,const ADbg& st);

    mutable int lvl;

};

#endif // ABSTRACT_DBG_H
