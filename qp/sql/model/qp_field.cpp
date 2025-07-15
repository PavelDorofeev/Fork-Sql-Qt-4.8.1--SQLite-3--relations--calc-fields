#include "qp_field.h"
#include <QDebug>

QpSqlField::QpSqlField( const QpSqlField::FLD_TYPE &Type,
                   const QString& fieldName)
    :
    QSqlField( fieldName ),
    type (Type)
{

}

QpSqlField& QpSqlField::operator=(const QSqlField& other)
{
    // ----------------------------------------------------
    // PblSqlField *fld = flds_ptr.value( afterColName )
    // ----------------------------------------------------

    qDebug() << "PblSqlField::operator= " <<other.d;


    return *this;

}
