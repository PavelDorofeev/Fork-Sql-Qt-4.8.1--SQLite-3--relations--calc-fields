#include "pblsqlrelationaltablemodel2.h"

#include "config2.h" // needs in your app

#include "pbltableview/my_sql.h"
#include <QDebug>
#include <QMessageBox>

PblSqlRelationalTableModel2::PblSqlRelationalTableModel2(QSqlDatabase &db ,
                                                         QObject *parent)
    :
      PblSqlRelationalTableModel(db,
                                 parent)
{

}

bool PblSqlRelationalTableModel2::setDependColumn(int src, int dest, int op, int col2)
{

    dependCol dd;

    dd.dst = dest;
    dd.op = op;
    dd.col2 = col2;

    dep.insert(src ,dd );

    return true;
}

bool PblSqlRelationalTableModel2::setSummaryColumns(int col)
{

    summaryColumns.insert(col,-1);

    return true;
}

bool PblSqlRelationalTableModel2::select()
{
    bool bbb= PblSqlRelationalTableModel::select();

    emit sig_column_values_changed( fieldIndex("sum") );

    return bbb;
}

bool PblSqlRelationalTableModel2::setData(const QModelIndex &idx, const QVariant &val, int role )
{

    if ( PblSqlRelationalTableModel::setData(idx , val , role) )
    {

        int srcCol = idx.column();

        if(summaryColumns.contains(srcCol))
            emit sig_column_values_changed( srcCol );


        if(dep.contains(srcCol))
        {
            int row = idx.row();

            dependCol dd = dep.value(srcCol);

            QModelIndex idx2 = index( row , dd.col2);

            QVariant val2 = data( idx2);

            if(dd.op == MULTI)
            {
                double res = val.toDouble() * val2.toDouble();

                QModelIndex idxRes = index( row , dd.dst);

                if ( ! PblSqlRelationalTableModel::setData( idxRes , res))
                {
                    return false;
                }

                if(summaryColumns.contains(dd.dst))
                    emit sig_column_values_changed( dd.dst );
            }

        }



        return true;
    }

    return false;
}

bool PblSqlRelationalTableModel2::prepare(const QString &tableName,
                                          const QHash<QString,QVariant> &SubAccountingFilter)
{
    if( PblSqlRelationalTableModel::prepare(tableName , SubAccountingFilter) )
    {

//        if ( ! config2::setting_mdl( this ) )
//        {
//            QMessageBox::warning(0,
//                                 mySql::error_,
//                                 tr("error in setting_mdl"),
//                                 "");
//            return false;
//        }

        return true;
    }
    return false;
}
