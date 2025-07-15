#include "qp_abstracttablemodel.h"

#include <QDebug>
#include <QMessageBox>

#include "qp/sql/model/qp_subaccnt.h"
#include "qp/sql/model/qp_columninfo.h"
#include "qp/sql/model/qp_calc_column.h"
#include "qp/sql/qp_sql.h"
#include "qp/core/dbg/dbg.h"

QpAbstractTableModel::QpAbstractTableModel()
      : priColName(QString())
      ,editable(false)
//      ,baseRec(this)

{

}

QpAbstractTableModel::~QpAbstractTableModel()
{
    clearContainers();
}


int QpAbstractTableModel::getPriColumn( ) const
{
    return baseRec.indexOf( priColName);
}


void QpAbstractTableModel::clearContainers()
{
    calc_columns.clear();
    defaultVls.clear();
    relations2.clear();
    subAccnt.clear();
    rel_bindings.clear();
    colInfo.clear();
    subAccountingFilter.clear();
    having.clear();
    specialFld.clear();
}

bool QpAbstractTableModel::isRelationalColumn(int col)
{
    QString fldName = baseRec.fieldName( col );

    Q_ASSERT(fldName.isEmpty()==false);

    if( relations2.contains(fldName))
        return true;

    return false;
}


QpSqlRelation QpAbstractTableModel::getRelationInfoForColumn(const QString &fldName)
{

    if( ! relations2.contains( fldName ))

        return QpSqlRelation();

    return relations2[fldName];
}


int QpAbstractTableModel::getRelIdColumn(int col) const
{

    if (  ! baseRec.field( col ).isValid() )

        return qp::db::COL_UNDEFINED;


    QString fldName = baseRec.fieldName( col );

    if( fldName.isEmpty() )

        return qp::db::COL_UNDEFINED;


    if( ! relations2.contains( fldName ) )

        return qp::db::COL_UNDEFINED;

    QpSqlRelation pp = relations2[ fldName ];

    QString relIdFldName = pp.get_ext_fld_name();

    return baseRec.indexOf( relIdFldName );


}
void QpAbstractTableModel::set_editable( bool Editable)
{
    editable = Editable;
}

