#include "config.h"
#include"pbltableview/PblSqlRelationalTableModel.h"
#include"pbltableview/pbltableview.h"
#include <QMessageBox>
#include "pbltableview/my_sql.h"
#include "pbltableview/btn_toolbox.h"
#include "pbltableview/some_tests.h"
#include <QObject>
#include <QSqlError>

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

    //mdl->setEditStrategy(QSqlTableModel::OnRowChange);



    if(tableName == "goods")
    {

        mdl->setAlignment(0, Qt::AlignCenter);

        mdl->setAlignment(2, Qt::AlignRight|Qt::AlignVCenter);
        mdl->setPrecision(2, 2);
        mdl->setDblFormat(2, 'f');

        mdl->setAlignment(3, Qt::AlignRight|Qt::AlignVCenter);
        mdl->setPrecision(3, 2);
        mdl->setDblFormat(3, 'f');

        mdl->setHeaderData(1 , Qt::Horizontal, "productName");

        CALC_COLUMN calc;

        calc.idField1           = mdl->baseRec.indexOf("id");
        calc.table              = "checks";
        calc.idField2           = "productName";
        calc.summaryField       = "sum";
        calc.calcFunc           = "sum";
        calc.calcFuncName_As = QObject::tr("sold");

        return mdl->setCalcField(calc);


    }
    else if(tableName == "checks")
    {
        mdl->setRelation(PblSqlRelation(1,
                                        mdl->baseRec.indexOf("productName"),
                                        "goods" ,
                                        "id" ,
                                        "productName"));

        mdl->setAlignment(0, Qt::AlignCenter);

        mdl->setPrecision(2,2);
        mdl->setAlignment(2, Qt::AlignRight|Qt::AlignVCenter);
        mdl->setDblFormat(2, 'f');

        mdl->setEditable( mdl->fieldIndex("sum") , false);

        return true;

    }
    else if(tableName == "purchases")
    {
        mdl->setAlignment(0, Qt::AlignCenter);

        mdl->setAlignment(2, Qt::AlignRight|Qt::AlignVCenter);
        mdl->setPrecision(2, 2);
        mdl->setDblFormat(2, 'f');

        mdl->setAlignment(3, Qt::AlignRight|Qt::AlignVCenter);
        mdl->setPrecision(3, 3);
        mdl->setDblFormat(3, 'f');

        mdl->setAlignment(4, Qt::AlignRight|Qt::AlignVCenter);
        mdl->setPrecision(4, 2);
        mdl->setDblFormat(4, 'f');

        if( ! mdl->setRelation( PblSqlRelation(1,
                                               mdl->baseRec.indexOf("productName"),
                                               "goods" ,
                                               "id" ,
                                               "productName")))
        {
            QMessageBox::critical(0 ,
                                  mySql::error_,
                                  QObject::tr("setRelation returns false"));
        }

        mdl->setHeaderData(1 , Qt::Horizontal, "productName");
        mdl->setAlignment(5, Qt::AlignCenter);

        // fields are only read
        mdl->setEditable( mdl->fieldIndex("sum") , false);

        //mdl->setEditStrategy(QSqlTableModel::OnFieldChange);

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



    /*
    if( editable )
    {
        PblTableView::ACTIONS acts = PblTableView::ACT_ALL_EDIT
                | PblTableView::ACT_SWITCH_EDIT_ENABLED
                | PblTableView::ACT_ALL_SEARCH;

        set_Actions(acts , editable);
    }

    PblTableView::ACTIONS acts = PblTableView::ACT_VIEW;

    set_Actions(acts , true);

    setEditState(editable);
    */

    QString tableName = view->model()->tableName();

    if(tableName == "purchases")
    {
        view->set_Actions( PblTableView::ACT_ALL , true);

        view->setComboBoxDelegate( 5 , QStringList() << "big" << "medium" << "small");

        view->setCheckBoxDelegate( 6 );

    }
    else if(tableName == "goods")
    {
        view->set_Actions( PblTableView::ACT_ALL , true);

    }
    else if(tableName == "checks")
    {
        view->set_Actions( PblTableView::ACT_ALL_SEARCH , true);

        view->setDateTimeDelegate( view->model()->fieldIndex("date_") );

        view->parentWidget()->setWindowTitle(tableName);
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
