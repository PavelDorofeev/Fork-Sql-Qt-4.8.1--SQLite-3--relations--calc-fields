#ifndef ORDERED_OBJ_H
#define ORDERED_OBJ_H

#include <QList>
#include <QMetaType>
#include <QVariantMap>
#include "pair.h"

#include "../dll_qp_core_global.h"

class LIB_PREFIX_QP_CORE OrderedObj
{
public:

    OrderedObj();
    OrderedObj(const QVariantMap & mm);
    //~OrderedObj();

    QList<Pair2> lst;

    void  fillFromQVariantMap( const QVariantMap &);

    QVariantMap toQVariantMap( ) const ;

    void toDebug( ) const ;
};

Q_DECLARE_METATYPE(OrderedObj);

#endif // ORDEREDOBJ_H
