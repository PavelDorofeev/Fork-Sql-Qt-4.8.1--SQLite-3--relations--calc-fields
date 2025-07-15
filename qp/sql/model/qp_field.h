#ifndef QP_FIELD_H
#define QP_FIELD_H

#include <QSqlField>

class QSqlField;
class QSqlFieldPrivate;

#include "qp/sql/dll_qp_sql_global.h"
class LIB_PREFIX_QP_SQL QpSqlField : public QSqlField
{

public:

    enum FLD_TYPE
    {
        FLD_BASED=0,
        FLD_RELATIOB,
        FLD_CALC
    };

    explicit QpSqlField(const QpSqlField::FLD_TYPE &type,
                      const QString& fieldName = QString());

    QpSqlField& operator=(const QSqlField& other);

    friend class QSqlField;

signals:
    
public slots:

private:


    FLD_TYPE type;

    
};

#endif // QP_FIELD_H
