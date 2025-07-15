#include "qp_sqltablemodel2.h"

#include "config.h" // needs in your app

#include <QDebug>
#include <QMessageBox>

QpSqlTableModel2::QpSqlTableModel2(QSqlDatabase &db ,
                                   QObject *parent)
    :
      QpSqlTableModel( db,
                      config::setting_mdl,
                      parent)
{

}

bool QpSqlTableModel2::setDependColumn(int src, int dest, int op, int col2)
{

    dependCol dd;

    dd.dst = dest;
    dd.op = op;
    dd.col2 = col2;

    dep.insert(src ,dd );

    return true;
}

bool QpSqlTableModel2::setSummaryColumns(int col)
{

    summaryColumns.insert(col,-1);

    return true;
}

bool QpSqlTableModel2::select()
{
    bool bbb= QpSqlTableModel::select();

    emit sig_column_values_changed(  baseRec.indexOf("sum") );

    return bbb;
}

bool QpSqlTableModel2::setData(const QModelIndex &idx, const QVariant &val, int role )
{

    if ( QpSqlTableModel::setData(idx , val , role) )
    {

        int srcCol = idx.column();

        if( summaryColumns.contains(srcCol))
            emit sig_column_values_changed( srcCol );


        if( dep.contains(srcCol))
        {
            int row = idx.row();

            dependCol dd = dep.value(srcCol);

            QModelIndex idx2 = index( row , dd.col2);

            QVariant val2 = data( idx2);

            if( dd.op == MULTI )
            {
                double res = val.toDouble() * val2.toDouble();

                QModelIndex idxRes = index( row , dd.dst);

                if ( ! QpSqlTableModel::setData( idxRes , res))
                {
                    return false;
                }

                if( summaryColumns.contains(dd.dst))
                    emit sig_column_values_changed( dd.dst );
            }

        }



        return true;
    }

    return false;
}

bool QpSqlTableModel2::prepare_mdl( const QString &tableName,
                                    const QHash<QString,QVariant> &SubAccountingFilter)
{
    if( QpSqlTableModel::prepare_mdl(tableName ,
                                     QStringList(),
                                     SubAccountingFilter) )
    {

        //        if ( ! config2::setting_mdl( this ) )
        //        {
        //            QMessageBox::warning(0,
        //                                 qp::dbg::error_,
        //                                 tr("error in setting_mdl"),
        //                                 "");
        //            return false;
        //        }

        return true;
    }
    return false;
}
