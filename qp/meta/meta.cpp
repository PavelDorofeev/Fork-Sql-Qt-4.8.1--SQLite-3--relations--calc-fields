#include "meta.h"
#include <QDebug>

namespace qp {


namespace meta {


bool cnct( const QObject * snd, const QString &sgn,
           const QObject * rcv, const QString &slt)
{

    if( ! QObject::connect ( snd , sgn.toLocal8Bit() , rcv , slt.toLocal8Bit() ) )
    {
        qCritical() << "!!!! Error connect(..) signal : " << sgn << " / slot : " << slt;

        QMessageBox::critical(0 ,
                              "Error signal/slot connect",
                              QString("Error connect(..):\n%1\n %2\n %3\n %4 ")
                              .arg (snd->objectName())
                              .arg(sgn)
                              .arg(rcv->objectName())
                              .arg(slt)
                              );

        return false;
    }

    return true;
}

bool dis_cnct( const QObject * snd, const QString &sgn,
           const QObject * rcv, const QString &slt)
{

    if( ! QObject::disconnect( snd , sgn.toLocal8Bit() , rcv , slt.toLocal8Bit() ) )
    {
        qCritical() << "!!!! Error connect(..) signal : " << sgn << " / slot : " << slt;

        QMessageBox::critical(0 ,
                              "Error signal/slot disconnect",
                              QString("Error disconnect(..):\n%1\n %2\n %3\n %4 ")
                              .arg (snd->objectName())
                              .arg(sgn)
                              .arg(rcv->objectName())
                              .arg(slt)
                              );

        return false;
    }

    return true;
}



}

}
