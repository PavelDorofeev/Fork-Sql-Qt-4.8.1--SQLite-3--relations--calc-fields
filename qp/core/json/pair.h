#ifndef PAIR_H
#define PAIR_H

#include <QString>
#include <QVariant>

#include "../dll_qp_core_global.h"

class LIB_PREFIX_QP_CORE Pair2 //: public QPair
{

public:
    Pair2();
    explicit Pair2(const QString& key , const QVariant & val);
    
    const QString key;
    const QVariant val;

private:
};

Q_DECLARE_METATYPE(Pair2);

#endif // PAIR_H
