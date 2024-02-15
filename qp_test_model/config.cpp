#include "config.h"
#include"qp/db/model/qp_sqltablemodel2.h"
#include"qp/db/view/qp_tableview_wrapper.h"
#include "qp/db/view/btn_toolbox.h"
#include "qp/db/view/some_tests.h"
#include "delegates/defaultstyleditemdelegate.h"

#include <QObject>
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>
#include <QHeaderView>

#include "qp/tableview/qp_tableview.h"
#include "qp/tableview/qp_horheaderview.h"
#include "qp/tableview/qp_vertheaderview.h"

#include "qp/dbg/dbg.h"
#include "qp/qp.h"
#include "qp/db/db.h"
#include "db1.h"

bool config::visibleRelIdColumns_byDefault = true;

char * config::prog_version = "7.0.0.1";

QpColumnInfo config::inf = QpColumnInfo( Qt::AlignRight | Qt::AlignHCenter , 2 );

config::config()
{
}



bool config::setting_mdl( QpSqlTableModel * mdl)
{
    if(! mdl)
        return false;

    if(mdl->tableName().isNull())
        return false;

    QString tableName = mdl->tableName();

    if(tableName == db1::TBL_GOODS)
    {

        mdl->setAlignment( db1::GOODS::ID , Qt::AlignCenter);
        mdl->setEditable( db1::GOODS::ID , false);

        mdl->setAlignment(db1::GOODS::PRODUCT_NAME_STR, Qt::AlignLeft|Qt::AlignVCenter);
        mdl->setAlignment(db1::GOODS::PRICE, Qt::AlignRight|Qt::AlignVCenter);
        mdl->setPrecision(db1::GOODS::PRICE, 2);
        mdl->setDblFormat(db1::GOODS::PRICE, 'f');


        // ------------------------------------------------------------------



        mdl->setCalcField( QpCalcColumn( db1::CHECK::QTY,
                                         db1::TBL_CHECKS,
                                         db1::CHECK::ID,
                                         db1::GOODS::PRODUCT_NAME_STR,
                                         "count",
                                         "qauntity"
                                         )
                           );

        mdl->setAlignment( db1::CHECK::QTY , Qt::AlignRight|Qt::AlignVCenter);
        mdl->setPrecision( db1::CHECK::QTY , 3);
        mdl->setDblFormat( db1::CHECK::QTY , 'f');

        // ------------------------------------------------------------------



        mdl->setCalcField( QpCalcColumn ( db1::CHECK::SUM,   // fields into external table (seprated by ,)
                                          db1::TBL_CHECKS,        // external table name
                                          db1::CHECK::ID,            //
                                          db1::GOODS::PRODUCT_NAME_STR,   //
                                          "sum",           // calc function name
                                          "summary"
                                          )
                           );

        // ------------------------------------------------------------------

        mdl->setAlignment( db1::CHECK::SUM , Qt::AlignRight|Qt::AlignVCenter);
        mdl->setPrecision( db1::CHECK::SUM , 2);
        mdl->setDblFormat( db1::CHECK::SUM , 'f');


    }
    else if(tableName == db1::TBL_SUB_ACCOUNTING)
    {

        mdl->setAlignment("id", Qt::AlignCenter);
        mdl->setEditable("id" , false );

        mdl->setAlignment("goods_id" , Qt::AlignRight|Qt::AlignVCenter);
        mdl->setEditable( "goods_id" , false );
        mdl->set_Visible( "goods_id" , false);

        mdl->setAlignment("val", Qt::AlignCenter|Qt::AlignVCenter);

        //mdl->setHeaderData("val") , Qt::Horizontal, "property");


        return true;

    }
    else if(tableName == db1::TBL_CHECKS)
    {
        mdl->setEditable( db1::CHECK::ID , false);
        mdl->setAlignment( db1::CHECK::ID , Qt::AlignCenter);

        mdl->setAlignment( db1::CHECK::PRODUCT_NAME , Qt::AlignLeft|Qt::AlignVCenter);
        mdl->setEditable( db1::CHECK::PRODUCT_NAME , false);

        // ---------------------------------------------------------------------

        if( ! mdl->setRelation( QpSqlRelation( db1::CHECK::PRODUCT_NAME,
                                               db1::TBL_GOODS ,
                                               db1::GOODS::ID ,
                                               db1::GOODS::PRODUCT_NAME_STR
                                               ) ) )
        {
            QMessageBox::critical(0 ,
                                  qp::dbg::error_,
                                  QObject::tr("setRelation returns false"));
        }


        // ---------------------------------------------------------------------

        if( ! mdl->setRelation( QpSqlRelation( db1::CHECK::SUB,
                                               db1::TBL_SUB_ACCOUNTING ,
                                               db1::SUB_ACCOUNTING::ID ,
                                               db1::SUB_ACCOUNTING::VAL
                                               ) ) )
        {
            QMessageBox::critical(0 ,
                                  qp::dbg::error_,
                                  QObject::tr("setRelation returns false"));
        }

        mdl->setEditable( db1::CHECK::SUB , false);
        mdl->setAlignment(db1::CHECK::SUB , Qt::AlignCenter);
        //mdl->setHeaderData("sub") , Qt:Horizontal, "sub");

        // ---------------------------------------------------------------------

//        mdl->setSubAccount( db1::TBL_GOODS , //"goods",
//                            db1::GOODS::PRODUCT_NAME_ID ,//"productName" ,
//                            db1::CHECK::SUB,//"sub",
//                            db1::SUB_ACCOUNTING::PRODUCT_NAME_ID,// ???? "goods_id",
//                            db1::GOODS::SUB_ON//"sub_on"
//                            );



        // ---------------------------------------------------------------------

        mdl->setPrecision("sum", 2);
        mdl->setAlignment("sum", Qt::AlignRight|Qt::AlignVCenter);
        mdl->setDblFormat("sum", 'f');
        mdl->setEditable( "sum" , false);


    }
    else if(tableName == db1::TBL_PURCHASES)
    {
        mdl->setAlignment("id", Qt::AlignCenter);

        mdl->setAlignment("productName", Qt::AlignLeft|Qt::AlignVCenter);

        mdl->setAlignment("sub", Qt::AlignCenter|Qt::AlignVCenter);
        mdl->setEditable( "sub", false );

        //mdl->setHeaderData("sub") , Qt::Horizontal, "sub");

        QpColumnInfo inf = QpColumnInfo();
        inf.precision = 2;
        inf.cFormat='f';
        inf.alignment = Qt::AlignRight|Qt::AlignVCenter;

        mdl->setColInf( "price" , inf );

        qDebug() << "price " << " precision " << mdl->colInfo.value( "price" ).precision;
        //        mdl->setAlignment("price", Qt::AlignRight|Qt::AlignVCenter);
        //        mdl->setPrecision("price", 2);
        //        mdl->setDblFormat("price", 'f');

        mdl->setAlignment("qty", Qt::AlignRight|Qt::AlignVCenter);
        mdl->setPrecision("qty", 3);
        mdl->setDblFormat("qty", 'f');

        mdl->setAlignment("sum", Qt::AlignRight|Qt::AlignVCenter);
        mdl->setPrecision("sum", 2);
        mdl->setDblFormat("sum", 'f');

        mdl->setAlignment("combobox", Qt::AlignCenter|Qt::AlignVCenter);


        // -----------------------------------------------------------------------

        QpSqlRelation rel( "productName",
                           "goods" ,
                           "id" ,
                           "productName"
                           );



        if( ! mdl->setRelation( rel))
        {
            QMessageBox::critical( 0 ,
                                   qp::dbg::error_,
                                   QObject::tr("setRelation returns false"));
        }


        QpSqlRelation relSubAcnt( "sub",
                                  "sub_accounting" ,
                                  "id" ,
                                  "val"
                                  );

        if( ! mdl->setRelation( relSubAcnt))
        {
            QMessageBox::critical(0 ,
                                  qp::dbg::error_,
                                  QObject::tr("setRelation returns false"));
        }


        mdl->setSubAccount( "goods",
                            "productName" ,
                            "sub",
                            "goods_id",
                            "sub_on");

        // -----------------------------------------------------------------------

        mdl->setEditable( "sum" , false); // only read


    }

    return true;
}

bool config::setting_view(QpTableViewWrapper *view)
{

    if(view == 0)
        return false;

    if(! view->model())

        return false;


    QpSqlTableModel * mdl = qobject_cast<QpSqlTableModel*>(view->model());

    if( ! mdl )
        return false;

    QString tableName = mdl->tableName();


    //view->set_ExtColumnsVisible(false, false);

    view->set_contextMenuEnabled(true); //

    if(view->selectable)
        view->set_editingEnabled(true , false, false);
    else
        view->set_editingEnabled(true , true, false);


    view->set_ExtColumnsVisible(true , false);

    view->set_editStrategyEnable(true);

    view->set_sortingEnabled(true);

    view->set_searchingEnabled(true);

    view->setShowGrid( true );
    //view->setShowBetweenRowBorder( true );

    if(tableName == db1::TBL_PURCHASES)
    {
        view->setComboBoxDelegate( db1::PURCHASES::COMBOBOX ,
                                   QStringList() << "big" << "medium" << "small");

        view->setCheckBoxDelegate( db1::PURCHASES::CHK );

        view->setDoubleWithPrecision(db1::PURCHASES::QTY , 3);


        //qp::db::SECTIONS_TMPL matrix = prepare_matrix_purch( mdl );

        ////view->init_template( matrix);

        //view->resizeColumnsToContents();

    }
    else if(tableName == db1::TBL_SUB_ACCOUNTING)
    {

    }
    else if(tableName == db1::TBL_GOODS)
    {
        //qp::db::SECTIONS_TMPL matrix = prepare_matrix_goods( mdl );

        ////view->init_template( matrix  );

        view->setCheckBoxDelegate( db1::GOODS::SUB_ON );

        //view->resizeColumnsToContents();
    }
    else if(tableName == db1::TBL_CHECKS)
    {

        view->set_editingEnabled( false );

        view->setDateTimeDelegate( db1::CHECK::DATE_TIME );

        view->parentWidget()->setWindowTitle(tableName);
    }

    // ----------------------------------------------------------
    //                      SEARCHING
    // ----------------------------------------------------------

    if ( mdl->isDefaultSearchingColumn != qp::db::COL_UNDEFINED )

        view->find_settings.searchedField = mdl->isDefaultSearchingColumn;
    else
    {
        for( int col =0; col < view->horizontalHeader()->count(); col++)
        {
            //            if(view->horizontalHeader()->isSectionHidden(col))
            //                continue;

            view->find_settings.searchedField = col; // first visible column

            break;
        }
    }


    // ----------------------------------------------------------
    //    for all remain columns set our default Delegate
    //    important for cell margins
    // ----------------------------------------------------------

    for(int col =0; col < mdl->columnCount(); col++)
    {
        if( ! view->itemDelegateForColumn( col ) && col != mdl->baseRec.indexOf("foo "))

            view->setDefaultDelegate( col );

    }

    //view->resizeColumnsToContents(); // Inreractive

    if(tableName == db1::TBL_TEST)
    {
        view->set_editingEnabled( true);

    }

    //view->horizontalHeader();
    //view->verticalHeader()->setIconSize( QSize (50,50));
    //view->verticalHeader()->setMinimumHeight( 70);
    //view->verticalHeader()->setFixedHeight( 70 );
    //view->resizeColumnsToContents();
    //view->resizeRowsToContents();


}


int config::get_defaultColumn( QpSqlTableModel * mdl)
{
    if(mdl->tableName().isNull())
        return false;

    QString tableName = mdl->tableName();


    if(tableName == "purchases")
    {
        return mdl->baseRec.indexOf("productName");
    }
    return 0;

}

bool config::set_newInsertedRowParameters_withSetData( QpSqlTableModel * mdl, int row)
{
    if(mdl->tableName().isNull())
        return false;

    QString tableName = mdl->tableName();


    if(tableName == "purchases")
    {
        QModelIndex idx = mdl->index( row , mdl->baseRec.indexOf("foo"));

        if( ! idx.isValid())
        {
            QMessageBox::warning( 0 ,
                                  qp::dbg::error_,
                                  QObject::tr("table '%1'\n\nindex row %2x%3 \n\n%4").
                                  arg(mdl->tableName()).
                                  arg(idx.row()).
                                  arg(idx.column()).
                                  arg(mdl->lastError().text()));
            return false;

        }

        if( ! mdl->setData(idx  , (int)1) );
        {
            QMessageBox::warning( 0 ,
                                  qp::dbg::error_,
                                  QString("setData returns false , table '%1'\n\n%2")
                                  .arg(mdl->tableName())
                                  .arg(mdl->lastError().text()));
            return false;
        }

        if(! idx.isValid() ) // submit() was done
            return false;

        return true;
    }

    return false;

}

bool config::set_newInsertedRowParameters( QpSqlTableModel * mdl, QSqlRecord & rec)
{
    if(mdl->tableName().isNull())
        return false;

    // -----------------------------------------------------------
    //              This is important!
    // new inserted row has not genereted (yes) flag in editBuffer for any fileds
    // we have to repare this

    for(int col=0; col < mdl->columnCount(); col++)
    {
        if(col == mdl->getPriColumn() )
            continue;

        rec.setGenerated( col , true ); // any col is not priCol will be generateg yes
        // with insertRow this is forbidden created fully empty row

    }
    // ------------------------------------------------------------


    QString tableName = mdl->tableName();

    if(tableName == "purchases")
    {


        return true;
    }

    return true;

}

bool config::test_model_is_correct( QSqlTableModel * mdl)
{
    if( mdl->rowCount() == 0)
    {
        QMessageBox::warning(0,
                             "Error in config::test_model_is_correct",
                             QString("table:%1,\nrowCount = 0!\nfirst you need select() for model")
                             .arg(mdl->tableName())
                             );
        return false;
    }

    return true;
}

qp::db::SECTIONS_TMPL config::prepare_matrix_goods( QAbstractTableModel * amdl)
{
    qp::db::SECTIONS_TMPL matrix;

    QpSqlTableModel * mdl = qobject_cast < QpSqlTableModel*>(amdl);

    if( ! mdl || ! test_model_is_correct( mdl) )
        return matrix;



    QList< qp::db::SECTION_D > line1;

    QList<int> lst;
    //lst.append( qp::db::indexOf( mdl, db1::PURCHASES::ID) );
    lst.append( qp::db::indexOf( mdl, db1::PURCHASES::PRODUCT_NAME_ID) );
    lst.append( qp::db::indexOf( mdl, db1::PURCHASES::PRICE) );

    foreach(int fld , lst )
        line1 << qp::db::SECTION_D( qp::db::MODEL_TYPE, fld );

    matrix.append( line1 );

    qp::db::print_matrix( matrix );


    mdl->setHeaderData( qp::db::indexOf( mdl,  db1::PURCHASES::PRODUCT_NAME_ID) , Qt::Horizontal,  " product name " );
    mdl->setHeaderData( qp::db::indexOf( mdl,  db1::PURCHASES::PRICE) , Qt::Horizontal,  " price [$] " );


    return matrix;
}


qp::db::SECTIONS_TMPL config::prepare_matrix_purch( QAbstractTableModel * amdl)
{
    qp::db::SECTIONS_TMPL matrix;

    QpSqlTableModel * mdl = qobject_cast < QpSqlTableModel*>(amdl);

    if( ! mdl )
        return matrix;


    QList< qp::db::SECTION_D > line1, line2;

    int PRODUCT_NAME_ID    = qp::db::indexOf( mdl,  db1::PURCHASES::PRODUCT_NAME_ID);
    int SUB    = qp::db::indexOf( mdl, db1::PURCHASES::SUB);
    int PRICE    = qp::db::indexOf( mdl, db1::PURCHASES::PRICE);
    int QTY    = qp::db::indexOf( mdl, db1::PURCHASES::QTY);
    int SUM    = qp::db::indexOf(mdl, db1::PURCHASES::SUM);

    line1 << qp::db::SECTION_D( qp::db::MODEL_TYPE, PRODUCT_NAME_ID );
    line1 << qp::db::SECTION_D( qp::db::MODEL_TYPE, PRICE );
    line1 << qp::db::SECTION_D( qp::db::MODEL_TYPE, SUM );

    line2 << qp::db::SECTION_D( qp::db::MODEL_TYPE, SUB );
    line2 << qp::db::SECTION_D( qp::db::MODEL_TYPE, QTY );
    line2 << qp::db::SECTION_D( qp::db::MODEL_TYPE, SUM );

    matrix.append( line1 );
    matrix.append( line2 );

    mdl->setHeaderData( qp::db::indexOf( mdl,  db1::PURCHASES::PRODUCT_NAME_ID) , Qt::Horizontal,  " product name " );
    mdl->setHeaderData( qp::db::indexOf( mdl,  db1::PURCHASES::PRICE) , Qt::Horizontal,  " price [$] " );
    mdl->setHeaderData( qp::db::indexOf( mdl,  db1::PURCHASES::QTY) , Qt::Horizontal,  " quantity " );
    mdl->setHeaderData( qp::db::indexOf( mdl,  db1::PURCHASES::SUM) , Qt::Horizontal,  " summary [$] " );
    mdl->setHeaderData( qp::db::indexOf( mdl,  db1::PURCHASES::CHK) , Qt::Horizontal,  " CHK " );
    mdl->setHeaderData( qp::db::indexOf( mdl,  db1::PURCHASES::COMBOBOX) , Qt::Horizontal,  "  COMBOBOX  " );


    qp::db::print_matrix( matrix );

    return matrix;
}
