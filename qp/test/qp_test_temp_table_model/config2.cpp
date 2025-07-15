#include "config2.h"

#include "qp_sqltablemodel2.h"

config2::config2()
{
}

bool config2::setting_mdl2(QpSqlTableModel2 * mdl)
{
    QString tblName = mdl->tableName();

    if(tblName == "purchases")
    {

        mdl->setDependColumn(mdl->baseRec.indexOf("price"),
                            mdl->baseRec.indexOf("sum"),
                            QpSqlTableModel2::MULTI,
                            mdl->baseRec.indexOf("qty")
                            );


        mdl->setDependColumn( mdl->baseRec.indexOf("qty"),
                            mdl->baseRec.indexOf("sum"),
                            QpSqlTableModel2::MULTI,
                            mdl->baseRec.indexOf("price")
                            );

        mdl->setSummaryColumns(mdl->baseRec.indexOf("sum"));

    }

    return true;
}
