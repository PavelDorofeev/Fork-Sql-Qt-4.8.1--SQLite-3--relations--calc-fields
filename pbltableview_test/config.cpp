#include "config.h"
#include"pbltableview/PblSqlRelationalTableModel.h"
#include"pbltableview/pbltableview.h"
#include <QMessageBox>
#include "pbltableview/my_sql.h"
#include "pbltableview/btn_toolbox.h"
#include "pbltableview/some_tests.h"
#include <QObject>

bool config::visibleRelIdColumns_byDefault = true;

config::config()
{
}

bool config::setting_mdl( PblSqlRelationalTableModel * mdl)
{
    if(mdl->tableName().isNull())
        return false;

    QString tableName = mdl->tableName();

    mdl->setEditStrategy(QSqlTableModel::OnRowChange);



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

        calc.idField1           = "id";
        calc.table              = "checks";
        calc.idField2           = "productName";
        calc.summaryField       = "sum";
        calc.calcFunc           = "sum";
        calc.calcFuncName_As = QObject::tr("sold");

        return mdl->setCalcField(calc);


    }
    else if(tableName == "checks")
    {
        mdl->setRelation(PblSqlRelation(1, "productName",  "goods" , "id" , "productName"));

        mdl->setAlignment(0, Qt::AlignCenter);

        mdl->setPrecision(2,2);
        mdl->setAlignment(2, Qt::AlignRight|Qt::AlignVCenter);
        mdl->setDblFormat(2, 'f');

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

        if( ! mdl->setRelation( PblSqlRelation(1, "productName", "goods" , "id" , "productName")))
        {
            QMessageBox::critical(0 ,
                                  mySql::error_,
                                  QObject::tr("setRelation returns false"));
        }

        mdl->setHeaderData(1 , Qt::Horizontal, "productName");
        mdl->setAlignment(5, Qt::AlignCenter);

        // fields are only read
        mdl->setEditable( mdl->fieldIndex("sum") , false);

        mdl->setEditStrategy(QSqlTableModel::OnFieldChange);

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

    view->initStrategy(view->model()->editStrategy());


    QString tableName = view->model()->tableName();

    if(tableName == "purchases")
    {
        view->setComboBoxDelegate( 5 , QStringList() << "big" << "small");

        view->setCheckBoxDelegate( 6 );

    }
    else
        view->parentWidget()->setWindowTitle(tableName);

    view->slot_setVisibleExRelIdColumns(config::visibleRelIdColumns_byDefault);

    view->setExRelIdColumnsVisible(true);

    view->resizeColumnsToContents();

    view->resizeRowsToContents();
}
