#include "pbltableview_purchases.h"
#include "PblSqlRelationalTableModel.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QSqlError>

PblTableView_Purchases::PblTableView_Purchases(PblSqlRelationalTableModel * mdl,
                                               QVBoxLayout * lo,
                                               QWidget *parent,
                                               bool editable) :
    PblTableView(mdl , lo , parent , editable)
{

}

void PblTableView_Purchases::commitData(QWidget *editor)
{
    QModelIndex index = currentIndex();

    if (!index.isValid())
        return;

    qDebug() << "PblTableView_Purchases::commitData editBuffer: " << mdl->getEditBuffer();

    // -------------------------------------------------------

    QAbstractItemView::commitData(editor);

    // -------------------------------------------------------

    int col = index.column();

    int row = index.row();
    if(col == mdl->fieldIndex("price")
            || col == mdl->fieldIndex("qty"))
    {


        QModelIndex sumIdx = mdl->index(row , mdl->fieldIndex("sum") );

        double sum = mdl->data(mdl->index(row , mdl->fieldIndex("price"))).toDouble() * mdl->data(mdl->index(row , mdl->fieldIndex("qty"))).toDouble();

        if( ! mdl->setData(sumIdx , sum, Qt::EditRole))
            QMessageBox::critical(this, "error" , "setData for sum field" + mdl->lastError().text());
    }


}
void PblTableView_Purchases::slot_dataChanged(QModelIndex idx1,QModelIndex idx2)
{
    //qDebug() << "slot_dataChanged";
}
