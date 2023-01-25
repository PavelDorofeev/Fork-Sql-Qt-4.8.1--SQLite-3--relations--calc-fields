#include "pblsqlrelationaltablemodel_purchases.h"
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>

PblSqlRelationalTableModel_Purchases::PblSqlRelationalTableModel_Purchases(QSqlDatabase &db,
                                                                           QObject *parent
                                                                           ) :
    PblSqlRelationalTableModel(db , parent)
{

}

bool PblSqlRelationalTableModel_Purchases::updateRowInTable(int row, const QSqlRecord &values)
{

    QSqlRecord rec = values;

    qDebug() << "PblSqlRelationalTableModel_Purchases::updateRowInTable "; // << rec;

    if(editStrategy() == QSqlTableModel::OnFieldChange)
    {
        if( rec.isGenerated("qty") )
        {
            double sum = data( index( row , rec.indexOf( "price"))).toDouble() *
                    rec.value("qty").toDouble();

            rec.setValue("sum" , sum);
            rec.setGenerated("sum" , true);
        }
        else if( rec.isGenerated("price") )
        {
            double sum = data( index( row , rec.indexOf( "qty"))).toDouble() *
                    rec.value("price").toDouble();

            rec.setValue("sum" , sum);
            rec.setGenerated("sum" , true);
        }
    }

    return PblSqlRelationalTableModel::updateRowInTable(row, rec);
}

bool PblSqlRelationalTableModel_Purchases::setData(
        const QModelIndex &idx,
        const QVariant &value,
        int role)
{
    int col = idx.column();

    int row = idx.row();

    /*if( editStrategy() == QSqlTableModel::OnFieldChange)  // look updateRowInTable
    {
        if ( rowMode( row ) != PblSqlRelationalTableModel::UPDATE)

            return PblSqlRelationalTableModel::setData(idx , value, role);
    }*/

    //qDebug() << "PblSqlRelationalTableModel_Purchases::setData";
    //qDebug() << "       " << record().fieldName(col) << value;

    if( ! PblSqlRelationalTableModel::setData(idx , value, role))
        return false;



    if( col == fieldIndex("price") || col == fieldIndex("qty"))
    {
        if( ! idx.isValid())
        {
            QMessageBox::critical(0,
                                  "error" ,
                                  tr("after setData ! idx.isValid().\n%1").
                                  arg( lastError().text()));
            return false;

        }
        QModelIndex sumIdx = index(row , fieldIndex("sum") );

        double sum = data(index(row , fieldIndex("price"))).toDouble() *
                data(index(row , fieldIndex("qty"))).toDouble();


        if( ! setData(sumIdx , sum, Qt::EditRole))
        {
            QMessageBox::critical(0,
                                  "error" ,
                                  tr("setData for sum field is wrong.\n%1").
                                  arg( lastError().text()));

            return true;
        }
    }

    return true;
}

