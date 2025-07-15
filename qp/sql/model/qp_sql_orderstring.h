#ifndef QP_SQL_ORDER_STRING_H
#define QP_SQL_ORDER_STRING_H

#include <QStringList>

#include "qp/sql/dll_qp_sql_global.h"

class LIB_PREFIX_QP_SQL QpSqlOrderString
{
public:

    QpSqlOrderString();

    QString fldName;
    Qt::SortOrder order;

    static const QString asc;// = " ASC";
    static const QString desc;// = " DESC";
    static const QString ord;// = " DESC";


    bool setSortFields( const QStringList& lst );

    QString getTxt();
private:
    QString resTxt;
};



#endif // QP_SQL_ORDER_STRING_H
