#include "pbltableview2.h"
#include <QDebug>
#include "pbltableview/pbl.h"


PblTableView2::PblTableView2(QWidget *parent,
                             cb_setting_mdl pMdl,
                             cb_setting_view pView,
                             bool selectable ) :
    PblTableView(parent,
                 pMdl,
                 pView,
                 selectable)
{

}

bool PblTableView2::vrt_insertRow(int row)
{
    // ------------------------------------------------------
    // this class must be uniqe for others application
    // ------------------------------------------------------

    //qDebug() << "editStrategy" << model()->editStrategy();

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
    int row = idx.row();

    if( col == model()->baseRec.indexOf("productName"))
    {
        if( ! idx.isValid())
        {

            Q_ASSERT( idRow > 0 );

            row = model()->findRowById( idRow) ;

            Q_ASSERT( row != pbl::ROW_UNDEFINED );



        }

        QVariant price = rec.value("price");

        int col = model()->baseRec.indexOf("price");

        model()->setData( model()->index( row , col) , price );


        col = model()->baseRec.indexOf("qty");

        model()->setData( model()->index( row , col) , 1.00 );


        //qDebug() << "rec " << rec;
    }
    else
    {

    }

    PblTableView::vrt_afterSetFldValue(idRow,
                                       col,
                                       idx, // ?????
                                       rec);
    resizeColumnsToContents();

    return true;
}
