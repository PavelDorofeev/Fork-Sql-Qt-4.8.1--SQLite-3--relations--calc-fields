#include "pblsqlrelationaltablemodel_purchases.h"
#include <QMessageBox>
#include <QSqlError>

PblSqlRelationalTableModel_Purchases::PblSqlRelationalTableModel_Purchases(QObject *parent,
                                                                           QSqlDatabase db) :
    PblSqlRelationalTableModel(parent , db)
{

}

bool PblSqlRelationalTableModel_Purchases::setData(
        const QModelIndex &idx,
        const QVariant &value,
        int role)
{
    int col = idx.column();

    int row = idx.row();

    if( ! PblSqlRelationalTableModel::setData(idx , value, role))
        return false;

    if(col == fieldIndex("price") || col == fieldIndex("qty"))
    {
        QModelIndex sumIdx = index(row , fieldIndex("sum") );

        double sum = data(index(row , fieldIndex("price"))).toDouble() * data(index(row , fieldIndex("qty"))).toDouble();


        if( ! setData(sumIdx , sum, Qt::EditRole))
        {
            QMessageBox::critical(0,
                                  "error" ,
                                  tr("setData for sum field is wrong.\n%1").arg( lastError().text()));

            return true;
        }
    }

    return true;
}

