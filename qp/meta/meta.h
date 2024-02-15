#ifndef META_H
#define META_H

#include <QObject>
#include <QMessageBox>

namespace qp {


namespace meta {


bool cnct( const QObject * snd, const QString & sgn,
           const QObject * rcv, const QString & slt);

bool dis_cnct( const QObject * snd, const QString & sgn,
           const QObject * rcv, const QString & slt);



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

#endif // META_H
