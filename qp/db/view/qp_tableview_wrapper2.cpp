#include "qp_tableview_wrapper2.h"
#include <QDebug>
#include "qp/db/model/qp_sqltablemodel.h"
#include "qp/gui/qp_gui.h"
#include "qp/db/db.h"


QpTableViewWrapper2::QpTableViewWrapper2( QWidget *parent,
                                          cb_setting_view pView,
                                          bool selectable ) :
    QpTableViewWrapper(parent,
                       pView,
                       selectable)
{

}

bool QpTableViewWrapper2::vrt_insertRow(int row)
{
    qWarning() << "QpTableViewWrapper2::vrt_insertRow( "<< row<< " )";

    // ------------------------------------------------------
    // this class must be uniqe for others application
    // ------------------------------------------------------

    //qDebug() << "editStrategy" << Model()->editStrategy();

    if ( QpTableViewWrapper::vrt_insertRow( row) )
    {
        int rr = currentIndex().row();

        int col = Model()->baseRec.indexOf("productName");

        QModelIndex goodIdx = Model()->index( rr , col );

        if( goodIdx.isValid())
        {
            bool needsSubmitAfter = false;

            return vrt_doubleClicked( goodIdx , needsSubmitAfter );

            return true;
        }

    }

    return false;
}

bool QpTableViewWrapper2::vrt_afterSetFldValue( int idRow,
                                                const QString & fldName,
                                                const QModelIndex & idx,
                                                const QpSqlRecord &rec,
                                                bool &needsSubmitAfter)
{
    int row = idx.row();

    if( fldName == "productName")
    {
        if( ! idx.isValid())
        {

            QP_ASSERT( idRow > 0 );

            row = Model()->findRowById( idRow) ;

            QP_ASSERT( row != qp::db::ROW_UNDEFINED );



        }

        QVariant price = rec.value("price");

        int col = Model()->baseRec.indexOf("price");

        Model()->setData( Model()->index( row , col) , price );


        col = Model()->baseRec.indexOf("qty");

        Model()->setData( Model()->index( row , col) , 1.00 );

        needsSubmitAfter = true;


        //qDebug() << "rec " << rec;
    }
    else
    {

    }

    QpTableViewWrapper::vrt_afterSetFldValue(idRow,
                                             fldName,
                                             idx, // ?????
                                             rec,
                                             needsSubmitAfter);

    return true;
}
