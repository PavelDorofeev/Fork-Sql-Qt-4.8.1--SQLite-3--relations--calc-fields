#ifndef QP_META_H
#define QP_META_H

#include <QObject>
//#include <QMessageBox>
#include <QString>
#include <QVariant>
#include "qp/core/meta/qhashbuilder.h"
#include "qp/core/meta/qpsingleshottimer.h"

#include "qp/core/dll_qp_core_global.h"

namespace qp {


namespace meta {


LIB_PREFIX_QP_CORE  bool cnct( const QObject * snd, const QString & sgn,
           const QObject * rcv, const QString & slt,
           Qt::ConnectionType type = Qt::AutoConnection);

LIB_PREFIX_QP_CORE bool dis_cnct( const QObject * snd, const QString & sgn,
           const QObject * rcv, const QString & slt);


LIB_PREFIX_QP_CORE bool saveToReestr(const QString &key , const QVariant& val);

LIB_PREFIX_QP_CORE QVariant initFromReestr(const QString &key ) ;

///static QString err1;

#ifdef THIS_IS_STATIC
/*
#define _CONNECT_(AA,BB,CC,DD) if(!connect(AA,BB,CC,DD)){\
    qCritical() << "!!!! Error connect(..) signal : " << BB << " / slot : " << DD;\
    }

#define _DISCONNECT_(AA,BB,CC,DD) if(!connect(AA,BB,CC,DD)){\
    qCritical() << "!!!! Error dis-connect(..) signal : " << BB << " / slot : " << DD;\
    }
*/
#else


/*
#define _CONNECT_(AA,BB,CC,DD) \
    if( ! connect ( AA , BB , CC ,DD )){\
    qCritical() << "!!!! Error connect(..) signal : " << BB << " / slot : " << DD;\
    QMessageBox::critical(0 , QString("Error connect(..) ") , AA->objectName()+"\n\t"+QString(BB)+"\n"+ CC->objectName()+"\n\t"+QString(DD));\
    qCritical() << "    " << AA->objectName();\
}

#define _DISCONNECT_(AA,BB,CC,DD) \
    if(!disconnect(AA,BB,CC,DD)){\
    qCritical() << "!!!! Error dis-connect(..) signal : " << BB << " / slot : " << DD;\
    QMessageBox::critical(0,"Error in function dis-connect(..)" , QString("%1\n  %2" ).arg(BB).arg((DD)));\
}
*/

#endif


}

}

#endif // QP_META_H
