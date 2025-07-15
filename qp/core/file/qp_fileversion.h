#ifndef QP_FILEVERSION_H
#define QP_FILEVERSION_H

//#include "windows.h"  DWORD = qint32
#include <QString>

#include "qp/core/dll_qp_core_global.h"
class LIB_PREFIX_QP_CORE QpFileVersion
{
public:
    qint32 vv1;
    qint32 vv2;
    qint32 vv3;
    qint32 vv4;

    void clear();
    QString toStr();
    bool isValid();

public:
    QpFileVersion();
};

#endif // QP_FILEVERSION_H
