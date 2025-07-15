#ifndef QP_SQLRECORD_H
#define QP_SQLRECORD_H

#include <QSqlRecord>
#include <QHash>

class QpCmnSqlTableModel;

#include "qp/sql/dll_qp_sql_global.h"
class LIB_PREFIX_QP_SQL QpSqlRecord : public QSqlRecord
{

public:


    QpSqlRecord();

    explicit QpSqlRecord( QpCmnSqlTableModel *mdl ,
                          const QSqlRecord &rec);

    QpSqlRecord& operator=(const QSqlRecord& other);

    virtual ~QpSqlRecord();

//    QHash< QString, SPECIAL_FLD_TYPES > specialFld;

    //    QHash< QString, int > relations; //

    int getRelIdCol(const QString& relCol) const;

    void setRefToModel(QpCmnSqlTableModel *mdl);

private:

    void func1(const QSqlRecord &rec);

    QpCmnSqlTableModel *mdl;


};

#endif // QP_SQLRECORD_H
