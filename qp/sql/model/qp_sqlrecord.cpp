#include "qp_sqlrecord.h"
#include "qp_field.h"
#include "qp/qp.h"
#include "qp/sql/qp_sql.h"
#include <QDebug>

#include "qp/sql/model/qp_cmnsqltablemodel.h"

QpSqlRecord::QpSqlRecord()
    :
      mdl(0)
//      priCol(-2)

{
    // --------------------------------------------
    //              default ctor
    // --------------------------------------------

}

QpSqlRecord::QpSqlRecord( QpCmnSqlTableModel *Mdl ,
                           const QSqlRecord &other)
    :
      QSqlRecord(other),
      mdl(Mdl)
{

//    qDebug() << "PblSqlRecord copying ctor " << other;

}


void QpSqlRecord::setRefToModel(QpCmnSqlTableModel *Mdl)
{
    mdl = Mdl;
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
//    qDebug() << "~QpSqlRecord() " << this;

//    specialFld.clear();
}

int QpSqlRecord::getRelIdCol(const QString& relColName) const
{

    if( mdl == 0 )
    {
        Q_ASSERT_X( 1==463454, "\n\nQpSqlRecord::getRelIdCol", "22222222222222");
        return qp::db::COL_UNDEFINED;
    }

    if( ! mdl->relations2.contains( relColName ))

        return qp::db::COL_UNDEFINED;


    QString relIdFldName = mdl->relations2[ relColName ].get_ext_fld_name();

    if( relIdFldName.isEmpty())

        return qp::db::COL_UNDEFINED;

    if( mdl->getBaseRec().contains( relIdFldName ))

        return mdl->getBaseRec().indexOf( relIdFldName );

    return qp::db::COL_UNDEFINED;

}
