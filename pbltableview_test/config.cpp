#include "config.h"
#include"pbltableview/PblSqlRelationalTableModel.h"
#include"pbltableview/pbltableview.h"
#include <QMessageBox>
#include "pbltableview/my_sql.h"
#include "pbltableview/btn_toolbox.h"
#include "pbltableview/some_tests.h"
#include <QObject>
#include <QSqlError>
#include <QHeaderView>

bool config::visibleRelIdColumns_byDefault = true;

char * config::prog_version = "7.0.0.1";


config::config()
{
}



bool config::setting_mdl( PblSqlRelationalTableModel * mdl)
{
    if(mdl->tableName().isNull())
        return false;

    QString tableName = mdl->tableName();

    if(tableName == "goods")
    {

        mdl->setAlignment(mdl->fieldIndex("id"), Qt::AlignCenter);
        mdl->setEditable(mdl->fieldIndex("id"), false);

        mdl->setAlignment(mdl->fieldIndex("price"), Qt::AlignRight|Qt::AlignVCenter);
        mdl->setPrecision(mdl->fieldIndex("price"), 2);
        mdl->setDblFormat(mdl->fieldIndex("price"), 'f');



        CALC_COLUMN calcQty;

         calcQty.idField1           = mdl->baseRec.indexOf("id");
         calcQty.extTblName         = "checks";
         calcQty.idField2Name       = "productName";
         calcQty.summaryField       = "qty";
         calcQty.calcFunc           = "sum";
         calcQty.calcFuncName_As    = QObject::tr("qty sold");
         calcQty.col                = mdl->baseRec.indexOf("productName");

         mdl->setCalcField(calcQty);

         mdl->setAlignment(4, Qt::AlignRight|Qt::AlignVCenter);
         mdl->setPrecision(4, 3);
         mdl->setDblFormat(4, 'f');

        CALC_COLUMN calcSum;

        calcSum.idField1           = mdl->baseRec.indexOf("id");
        calcSum.extTblName         = "checks";
        calcSum.idField2Name       = "productName";
        calcSum.summaryField       = "sum";
        calcSum.calcFunc           = "sum";
        calcSum.calcFuncName_As    = QObject::tr("sum sold");
        calcSum.col                = mdl->baseRec.indexOf("productName");

        mdl->setCalcField(calcSum);

        mdl->setAlignment(5, Qt::AlignRight|Qt::AlignVCenter);
        mdl->setPrecision(5, 2);
        mdl->setDblFormat(5, 'f');


        return true;


    }
    else if(tableName == "sub_accounting")
    {

        mdl->setAlignment(mdl->fieldIndex("id"), Qt::AlignCenter);
        mdl->setEditable(mdl->fieldIndex("id") , false );

        mdl->setAlignment(mdl->fieldIndex("goods_id"), Qt::AlignRight|Qt::AlignVCenter);
        mdl->setEditable(mdl->fieldIndex("goods_id") , false );

        mdl->setAlignment(mdl->fieldIndex("val"), Qt::AlignLeft|Qt::AlignVCenter);

        mdl->setHeaderData(mdl->fieldIndex("val") , Qt::Horizontal, "property");



        return true;

    }
    else if(tableName == "checks")
    {
        mdl->setEditable(mdl->fieldIndex("id"), false);
        mdl->setAlignment(mdl->fieldIndex("id"), Qt::AlignCenter);

        mdl->setRelation(PblSqlRelation( mdl->baseRec.indexOf("productName"),
                                        "goods" ,
                                        "id" ,
                                        "productName"));

       mdl->setHeaderData(mdl->fieldIndex("productName") , Qt::Horizontal, "productName");

        mdl->setEditable(mdl->fieldIndex("productName"), false);


        PblSqlRelation relSubAcnt( mdl->fieldIndex("sub"),
                                   "sub_accounting" ,
                                   "id" ,
                                   "val"
                                   );

        mdl->setEditable(mdl->fieldIndex("sub"), false);
        mdl->setHeaderData(mdl->fieldIndex("sub") , Qt::Horizontal, "sub");

        relSubAcnt.srvSubAcntParentFld = QString("goods_id");
        relSubAcnt.subPrntAcntColumn = mdl->fieldIndex("productName");

        if( ! mdl->setRelation( relSubAcnt))
        {
            QMessageBox::critical(0 ,
                                  mySql::error_,
                                  QObject::tr("setRelation returns false"));
        }


        mdl->setBinding( mdl->fieldIndex("productName") , mdl->fieldIndex("sub")); // !!!

        mdl->setPrecision(mdl->fieldIndex("sum"), 2);
        mdl->setAlignment(mdl->fieldIndex("sum"), Qt::AlignRight|Qt::AlignVCenter);
        mdl->setDblFormat(mdl->fieldIndex("sum"), 'f');
        mdl->setEditable( mdl->fieldIndex("sum") , false);

        return true;

    }
    else if(tableName == "purchases")
    {
        mdl->setAlignment(mdl->fieldIndex("id"), Qt::AlignCenter);

        mdl->setAlignment(mdl->fieldIndex("price"), Qt::AlignRight|Qt::AlignVCenter);
        mdl->setPrecision(mdl->fieldIndex("price"), 2);
        mdl->setDblFormat(mdl->fieldIndex("price"), 'f');

        mdl->setAlignment(mdl->fieldIndex("qty"), Qt::AlignRight|Qt::AlignVCenter);
        mdl->setPrecision(mdl->fieldIndex("qty"), 3);
        mdl->setDblFormat(mdl->fieldIndex("qty"), 'f');

        mdl->setAlignment(mdl->fieldIndex("sum"), Qt::AlignRight|Qt::AlignVCenter);
        mdl->setPrecision(mdl->fieldIndex("sum"), 2);
        mdl->setDblFormat(mdl->fieldIndex("sum"), 'f');

        // -----------------------------------------------------------------------

        PblSqlRelation rel( mdl->fieldIndex("productName"),
                            "goods" ,
                            "id" ,
                            "productName"
                            );

        mdl->addSubAcntOnField( rel ,
                                mdl->fieldIndex("productName") ,
                                mdl->fieldIndex("sub") ,
                                "sub_on" );


        if( ! mdl->setRelation( rel))
        {
            QMessageBox::critical( 0 ,
                                   mySql::error_,
                                   QObject::tr("setRelation returns false"));
        }

        mdl->setHeaderData(1 , Qt::Horizontal, "productName");
        mdl->setAlignment(5, Qt::AlignCenter);


        PblSqlRelation relSubAcnt( mdl->fieldIndex("sub"),
                                   "sub_accounting" ,
                                   "id" ,
                                   "val"
                                   );

        relSubAcnt.srvSubAcntParentFld = QString("goods_id");
        relSubAcnt.subPrntAcntColumn = mdl->fieldIndex("productName");

        if( ! mdl->setRelation( relSubAcnt))
        {
            QMessageBox::critical(0 ,
                                  mySql::error_,
                                  QObject::tr("setRelation returns false"));
        }


        mdl->setBinding( mdl->fieldIndex("productName") , mdl->fieldIndex("sub")); // !!!

        // -----------------------------------------------------------------------

        mdl->setEditable( mdl->fieldIndex("sum") , false); // only read


        return true;
    }

    return false;
}

bool config::setting_view(PblTableView *view)
{

    if(view == 0)
        return false;

    if(view->model()->tableName().isNull())
        return false;


    PblTableView::ACTIONS act = PblTableView::ACT_ALL;

    PblSqlRelationalTableModel * mdl = view->model();

    QString tableName = view->model()->tableName();

    if(tableName == "purchases")
    {
        view->set_Actions( PblTableView::ACT_ALL , true);

        view->setComboBoxDelegate( mdl->fieldIndex("cmb") , QStringList() << "big" << "medium" << "small");

        view->setCheckBoxDelegate( mdl->fieldIndex("chk") );

    }
    else if(tableName == "sub_accounting")
    {
        view->set_Actions( PblTableView::ACT_ALL , true);

    }
    else if(tableName == "goods")
    {
        view->set_Actions( PblTableView::ACT_ALL , true);

        view->setCheckBoxDelegate( mdl->fieldIndex("sub_on") );
    }
    else if(tableName == "checks")
    {
        view->set_Actions( PblTableView::ACT_ALL_SEARCH , true);

        view->setDateTimeDelegate( mdl->fieldIndex("date_") );

        view->parentWidget()->setWindowTitle(tableName);
    }

    // ----------------------------------------------------------
    //                      SEARCHING
    // ----------------------------------------------------------

    if ( mdl->isDefaultSearchingColumn != PblSqlRelationalTableModel::FLD_UNDEFINED )

           view->find_settings.searchedField = mdl->isDefaultSearchingColumn;
    else
    {
        for( int col =0; col < view->horizontalHeader()->count(); col++)
        {
            if(view->horizontalHeader()->isSectionHidden(col))
                continue;

            view->find_settings.searchedField = col; // first visible column

            break;
        }
    }

    view->set_Actions(PblTableView::ACT_SHOW_EXTENDED_RELATION_COLUMNS , config::visibleRelIdColumns_byDefault);

    view->resizeColumnsToContents();

    view->resizeRowsToContents();
}


int config::get_defaultColumn( PblSqlRelationalTableModel * mdl)
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

bool config::set_newInsertedRowParameters_withSetData( PblSqlRelationalTableModel * mdl, int row)
{
    if(mdl->tableName().isNull())
        return false;

    QString tableName = mdl->tableName();


    if(tableName == "purchases")
    {
        QModelIndex idx = mdl->index( row , mdl->fieldIndex("foo"));

        if( ! idx.isValid())
        {
            QMessageBox::warning( 0 ,
                                  mySql::error_,
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
                                  mySql::error_,
                                  QObject::tr("setData returns false , table '%1'\n\n%2").
                                  arg(mdl->tableName()).arg(mdl->lastError().text()));
            return false;
        }

        if(! idx.isValid() ) // submit() was done
            return false;

        return true;
    }

    return false;

}

bool config::set_newInsertedRowParameters( PblSqlRelationalTableModel * mdl, QSqlRecord & rec)
{
    if(mdl->tableName().isNull())
        return false;

    // -----------------------------------------------------------
    //              This is important!
    // new inserted row has not genereted (yes) flag in editBuffer for any fileds
    // we have to repare this

    for(int col=0; col < mdl->columnCount(); col++)
    {
        if(col == mdl->priCol)
            continue;

        rec.setGenerated( col , true ); // any col is not priCol will be generateg yes
        // with insertRow this is forbidden created fully empty row

    }
    // ------------------------------------------------------------


    QString tableName = mdl->tableName();

    if(tableName == "purchases")
    {

        //rec.setValue( mdl->fieldIndex("foo") , (int)1);
        //rec.setGenerated( mdl->fieldIndex("foo") , true );

        //rec.setValue(mdl->fieldIndex("cmb") , 0);
        //rec.setGenerated( mdl->fieldIndex("cmb") , true );

        return true;
    }

    return true;

}
