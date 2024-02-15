#include "db.h"
#include <QMessageBox>
#include "qp/db/model/qp_sqltablemodel.h"

namespace qp
{

namespace db
{

CELL_NODES::CELL_NODES( int num1 )
    :
      left( num1 ),
      top( num1 ),
      right( num1 ),
      bottom( num1 ),
      visible( true )
{

}

int indexOf( const QpSqlTableModel *mdl, const QString &fldName )
{
    int res = mdl->record().indexOf( fldName);

    if( res <0 )
    {
        QMessageBox::warning( 0,
                              "Error",
                              QString("table:%2,\nundefined field %1")
                              .arg(fldName)
                              .arg(mdl->tableName())
                              );
    }

    return res;
}

void print_matrix( const qp::db::SECTIONS_TMPL &matrix, QString &header  )
{
    qDebug() << header;

    for(int line=0;line< matrix.count(); line++)
    {
        QString str2;

        for(int xNum=0;xNum< matrix[ line] .count(); xNum++)
        {
            if( ! str2.isEmpty())
                str2.append(",");

            str2.append( QString::number(matrix[ line] [ xNum].logicalNumber) );
        }

        qDebug()<< "    "<<str2;
    }

}

}

}

