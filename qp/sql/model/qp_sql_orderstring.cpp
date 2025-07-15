#include "qp_sql_orderstring.h"


const QString QpSqlOrderString::asc = " ASC";
const QString QpSqlOrderString::desc = " DESC";
const QString QpSqlOrderString::ord = " ORDER BY ";

QpSqlOrderString::QpSqlOrderString()
    :
      fldName(QString()),
      order( Qt::AscendingOrder)
{

}

QString QpSqlOrderString::getTxt()
{
    if( fldName.isEmpty() )
        return "";

    return ord + fldName + ( order == Qt::AscendingOrder ?  asc : desc) ;
}


bool QpSqlOrderString::setSortFields( const QStringList& lst )
{
    fldName.clear();

    for( int ii = 0 ; ii < lst.count(); ii++)
    {
        if( ! fldName.isEmpty())
            fldName.append(",");

        fldName.append( lst.at( ii ));
    }

    return true;
}
