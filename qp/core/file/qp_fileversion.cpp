#include "qp_fileversion.h"

#include <QString>

QpFileVersion::QpFileVersion():
    vv1(-1),
    vv2(-1),
    vv3(-1),
    vv4(-1)
{
    clear();
}


QString QpFileVersion::toStr()
{
    return QString("%1.%2.%3.%4")
            .arg(vv1)
            .arg(vv2)
            .arg(vv3)
            .arg(vv4);
}

bool QpFileVersion::isValid()
{
    if( vv1 == -1)
        return false;
    else if( vv2 == -1)
        return false;
    else if( vv3 == -1)
        return false;
    else if( vv4 == -1)
        return false;

    return true;
}

void QpFileVersion::clear()
{
    vv1 = -1;
    vv2 = -1;
    vv3 = -1;
    vv4 = -1;
}
