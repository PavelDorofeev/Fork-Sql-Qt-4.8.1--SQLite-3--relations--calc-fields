#include "config.h"
#include"pbltableview/PblSqlRelationalTableModel.h"
#include"pbltableview/pbltableview.h"
#include <QMessageBox>
#include "pbltableview/my_sql.h"
#include "pbltableview/btn_toolbox.h"
#include "pbltableview/some_tests.h"
#include "pbltableview/defaultstyleditemdelegate.h"
#include <QObject>
#include <QSqlError>
#include <QDebug>
#include <QHeaderView>

bool config::visibleRelIdColumns_byDefault = true;

char * config::prog_version = "7.0.0.1";

PblColumnInfo config::inf = PblColumnInfo( Qt::AlignRight | Qt::AlignHCenter , 2 );

config::config()
{
}



bool config::setting_mdl( PblSqlRelationalTableModel * mdl)
{
    if(! mdl)
        return false;

    if(mdl->tableName().isNull())
        return false;

    QString tableName = mdl->tableName();

    if(tableName == "goods")
    {

        mdl->setAlignment("id", Qt::AlignCenter);
        mdl->setEditable("id", false);

        mdl->setAlignment("productName", Qt::AlignLeft|Qt::AlignVCenter);
        mdl->setAlignment("price", Qt::AlignRight|Qt::AlignVCenter);
        mdl->setPrecision("price", 2);
        mdl->setDblFormat("price", 'f');


        // ------------------------------------------------------------------

        PblCalcColumn qty( "qty",
                           "checks",
                           "id",
                           "productName",
                           "sum",
                           "quantity"
                           );

        mdl->setCalcField( qty );

        mdl->setAlignment("qty", Qt::AlignRight|Qt::AlignVCenter);
        mdl->setPrecision("qty", 3);
        mdl->setDblFormat("qty", 'f');

        // ------------------------------------------------------------------

        PblCalcColumn sum( "sum",           // fields into external table (seprated by ,)
                           "checks",        // external table name
                           "id",            //
                           "productName",   //
                           "sum",           // calc function name
                           "summary"
                           );

        mdl->setCalcField( sum );

        // ------------------------------------------------------------------

        mdl->setAlignment("sum", Qt::AlignRight|Qt::AlignVCenter);
        mdl->setPrecision("sum", 2);
        mdl->setDblFormat("sum", 'f');


    }
    else if(tableName == "sub_accounting")
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
    else if(tableName == "checks")
    {
        mdl->setEditable("id", false);
        mdl->setAlignment("id", Qt::AlignCenter);

        mdl->setAlignment("productName", Qt::AlignLeft|Qt::AlignVCenter);


        if( ! mdl->setRelation(
                    PblSqlRelation( "productName",
                                    "goods" ,
                                    "id" ,
                                    "productName")))
        {
            QMessageBox::critical(0 ,
                                  mySql::error_,
                                  QObject::tr("setRelation returns false"));

        }


        //mdl->setHeaderData("productName") , Qt::Horizontal, "productName");

        mdl->setEditable("productName", false);





        if( ! mdl->setRelation(
                    PblSqlRelation( "sub",
                                    "sub_accounting" ,
                                    "id" ,
                                    "val"
                                    ) ) )
        {
            QMessageBox::critical(0 ,
                                  mySql::error_,
                                  QObject::tr("setRelation returns false"));
        }

        mdl->setEditable("sub", false);
        mdl->setAlignment("sub", Qt::AlignCenter);
        //mdl->setHeaderData("sub") , Qt::Horizontal, "sub");

        // ---------------------------------------------------------------------

        mdl->setSubAccount( "goods",
                            "productName" ,
                            "sub",
                            "goods_id",
                            "sub_on");

        // ---------------------------------------------------------------------

        mdl->setPrecision("sum", 2);
        mdl->setAlignment("sum", Qt::AlignRight|Qt::AlignVCenter);
        mdl->setDblFormat("sum", 'f');
        mdl->setEditable( "sum" , false);


    }
    else if(tableName == "purchases")
    {
        mdl->setAlignment("id", Qt::AlignCenter);

        mdl->setAlignment("productName", Qt::AlignLeft|Qt::AlignVCenter);

        mdl->setAlignment("sub", Qt::AlignCenter|Qt::AlignVCenter);
        mdl->setEditable( "sub", false );

        //mdl->setHeaderData("sub") , Qt::Horizontal, "sub");

        PblColumnInfo inf = PblColumnInfo();
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

        PblSqlRelation rel( "productName",
                            "goods" ,
                            "id" ,
                            "productName"
                            );



        if( ! mdl->setRelation( rel))
        {
            QMessageBox::critical( 0 ,
                                   mySql::error_,
                                   QObject::tr("setRelation returns false"));
        }


        PblSqlRelation relSubAcnt( "sub",
                                   "sub_accounting" ,
                                   "id" ,
                                   "val"
                                   );

        if( ! mdl->setRelation( relSubAcnt))
        {
            QMessageBox::critical(0 ,
                                  mySql::error_,
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

bool config::setting_view(PblTableView *view)
{

    if(view == 0)
        return false;

    if(! view->model())

        return false;

    if(view->model()->tableName().isNull())

        return false;

    //PblTableView::ACTIONS act = PblTableView::ACT_ALL;

    PblSqlRelationalTableModel * mdl = view->model();

    QString tableName = view->model()->tableName();


    view->set_ExtColumnsVisible(false, false);

    view->set_contextMenuEnabled(true); //

    if(view->selectable)
        view->set_editingEnabled(true , false, false);
    else
        view->set_editingEnabled(true , true, false);


    view->set_ExtColumnsVisible(true , false);

    view->set_editStrategyEnable(true);

    view->set_sortingEnabled(true);

    view->set_searchingEnabled(true);

    if(tableName == "purchases")
    {
        view->setComboBoxDelegate( "combobox" ,
                                   QStringList() << "big" << "medium" << "small");

        view->setCheckBoxDelegate( "chk" );

        view->setDoubleWithPrecision("qty" , 3);

    }
    else if(tableName == "sub_accounting")
    {

    }
    else if(tableName == "goods")
    {
        view->setCheckBoxDelegate( "sub_on" );
    }
    else if(tableName == "checks")
    {

        view->set_editingEnabled( false );

        view->setDateTimeDelegate( "date_" );

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


    // ----------------------------------------------------------
    //    for all remain columns set our default Delegate
    //    important for cell margins
    // ----------------------------------------------------------

    for(int col =0; col < mdl->columnCount(); col++)
    {
        if( ! view->itemDelegateForColumn( col ) && col != mdl->baseRec.indexOf("foo "))

            view->setDefaultDelegate( col );

    }





    view->resizeColumnsToContents(); // Inreractive


    //view->resizeRowsToContents();

    qDebug() << "verticalHeader()->resizeMode()";

    for(int row=0; row < mdl->rowCount(); row++)
    {
        qDebug() << "   row " << row <<  view->verticalHeader()->resizeMode(row);
    }

    qDebug() << "horizontalHeader()->resizeMode()";

    for(int col=0; col < mdl->columnCount(); col++)
    {
        //qDebug() << "   col " << col << view->horizontalHeader()->resizeMode(col);
    }

    //    qDebug() << "   lineWidth " << view->lineWidth();
    //    qDebug() << "   rowHeight(0)" << view->rowHeight(0);
    //    qDebug() << "   wordWrap()" << view->wordWrap();
    //    qDebug() << "   tabKeyNavigation()" << view->tabKeyNavigation();

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
        QModelIndex idx = mdl->index( row , mdl->baseRec.indexOf("foo"));

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
