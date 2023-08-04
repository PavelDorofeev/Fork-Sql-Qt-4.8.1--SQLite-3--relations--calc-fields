#include "pblsqlrecord.h"
#include "pblfield.h"
#include "pbl.h"
#include <QDebug>

#include "pblsqlrelationaltablemodel.h"

PblSqlRecord::PblSqlRecord()
//    :
//      priCol(-2)

{
    // --------------------------------------------
    //              default ctor
    // --------------------------------------------

}

PblSqlRecord::PblSqlRecord( PblSqlRelationalTableModel &Mdl ,
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

PblSqlRecord& PblSqlRecord::operator=(const QSqlRecord& other)
{
    func1(other); //!!!

    //qDebug() << "PblSqlRecord::operator=  &other " << &other << " this " << this << " this* " << *this;


    return *this;
}

void PblSqlRecord::func1(const QSqlRecord &other)
{
    //    d = other.d;
    //    d->ref.ref();

    qAtomicAssign(d, other.d);

}
PblSqlRecord::~PblSqlRecord()
{
    qDebug() << "~PblSqlRecord() " << this;
}

int PblSqlRecord::isThis_RelExtColumn(const QString& relColName) const
{
    /*
    SELECT purchases.id,
    relTbl_1.productName AS productName_id_1_productName, //!!!!!
    purchases.price,
    purchases.qty,
    */

    if( ! mdl->relations2.contains( relColName ))

        return pbl::COL_UNDEFINED;


    QString relIdFldName = mdl->relations2[ relColName ].get_ext_fld_name();

    if( relIdFldName.isEmpty())

        return pbl::COL_UNDEFINED;

    if( mdl->baseRec.contains( relIdFldName ))

        return mdl->baseRec.indexOf( relIdFldName );


    return pbl::COL_UNDEFINED;


}
