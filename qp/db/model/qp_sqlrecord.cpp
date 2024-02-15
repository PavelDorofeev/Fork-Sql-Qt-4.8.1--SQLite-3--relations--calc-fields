#include "qp_sqlrecord.h"
#include "qp_field.h"
#include "qp/qp.h"
#include "qp/db/db.h"
#include <QDebug>

#include "qp/db/model/qp_sqltablemodel.h"

QpSqlRecord::QpSqlRecord()
//    :
//      priCol(-2)

{
    // --------------------------------------------
    //              default ctor
    // --------------------------------------------

}

QpSqlRecord::QpSqlRecord( QpSqlTableModel &Mdl ,
                           const QSqlRecord &other)
    :
      QSqlRecord(other),
      mdl(&Mdl)
{

    qDebug() << "PblSqlRecord copying ctor " << other;

    // --------------------------------------------
    //              copying ctor
    // --------------------------------------------



}

QpSqlRecord& QpSqlRecord::operator=(const QSqlRecord& other)
{
    func1(other); //!!!

    //qDebug() << "PblSqlRecord::operator=  &other " << &other << " this " << this << " this* " << *this;


    return *this;
}

void QpSqlRecord::func1(const QSqlRecord &other)
{
    //    d = other.d;
    //    d->ref.ref();

    qAtomicAssign(d, other.d);

}
QpSqlRecord::~QpSqlRecord()
{
    qDebug() << "~PblSqlRecord() " << this;

    specialFld.clear();
}

int QpSqlRecord::getRelIdCol(const QString& relColName) const
{
    /*
    SELECT purchases.id,
    relTbl_1.productName AS productName_id_1_productName, //!!!!!
    purchases.price,
    purchases.qty,
    */

    if( ! mdl->relations2.contains( relColName ))

        return qp::db::COL_UNDEFINED;


    QString relIdFldName = mdl->relations2[ relColName ].get_ext_fld_name();

    if( relIdFldName.isEmpty())

        return qp::db::COL_UNDEFINED;

    if( mdl->baseRec.contains( relIdFldName ))

        return mdl->baseRec.indexOf( relIdFldName );


    return qp::db::COL_UNDEFINED;


}
