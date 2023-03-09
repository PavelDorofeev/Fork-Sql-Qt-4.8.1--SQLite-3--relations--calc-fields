#include "pbltableview2.h"
#include <QDebug>


PblTableView2::PblTableView2(QWidget *parent,
                             bool editable ,
                             bool selectable ) :
    PblTableView(parent,
                 editable ,
                 selectable)
{

}

bool PblTableView2::vrt_insertRow(int row)
{

    if ( PblTableView::vrt_insertRow( row) )
    {
        int rr = currentIndex().row();
        int col = model()->baseRec.indexOf("productName");

        QModelIndex goodIdx = model()->index( rr , col );

        if( goodIdx.isValid())
        {
            vrt_doubleClicked( goodIdx );

            return true;
        }
    }

    return false;
}

bool PblTableView2::vrt_afterSetFldValue(int idRow,
                                         int col,
                                         const QModelIndex & idx,
                                         const PblSqlRecord &rec)
{

    if( col == model()->baseRec.indexOf("productName"))
    {
        if( idx.isValid())
        {
            QVariant price = rec.value("price");

            int col = model()->baseRec.indexOf("price");

            model()->setData( model()->index( idx.row() , col) , price );


            col = model()->baseRec.indexOf("qty");

            model()->setData( model()->index( idx.row() , col) , 1.00 );

        }
        //qDebug() << "rec " << rec;
    }
    else
    {

    }

    PblTableView::vrt_afterSetFldValue(idRow,
                                       col,
                                       idx,
                                       rec);
    resizeColumnsToContents();

    return true;
}
