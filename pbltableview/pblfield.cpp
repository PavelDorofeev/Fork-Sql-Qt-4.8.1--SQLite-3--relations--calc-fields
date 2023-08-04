#include "pblfield.h"
#include <QDebug>

PblSqlField::PblSqlField( const PblSqlField::FLD_TYPE &Type,
                   const QString& fieldName)
    :
    QSqlField( fieldName ),
    type (Type)
{

}

PblSqlField& PblSqlField::operator=(const QSqlField& other)
{
    // ----------------------------------------------------
    // PblSqlField *fld = flds_ptr.value( afterColName )
    // ----------------------------------------------------

    qDebug() << "PblSqlField::operator= " <<other.d;


    return *this;

}
