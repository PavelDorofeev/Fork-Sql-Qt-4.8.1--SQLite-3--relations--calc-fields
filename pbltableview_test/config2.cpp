#include "config2.h"

#include "pbltableview/PblSqlRelationalTableModel2.h"

config2::config2()
{
}

bool config2::setting_mdl2(PblSqlRelationalTableModel2 * mdl)
{
    QString tblName = mdl->tableName();

    if(tblName == "purchases")
    {

        mdl->setDependColumn(mdl->baseRec.indexOf("price"),
                            mdl->baseRec.indexOf("sum"),
                            PblSqlRelationalTableModel2::MULTI,
                            mdl->baseRec.indexOf("qty")
                            );


        mdl->setDependColumn( mdl->baseRec.indexOf("qty"),
                            mdl->baseRec.indexOf("sum"),
                            PblSqlRelationalTableModel2::MULTI,
                            mdl->baseRec.indexOf("price")
                            );

        mdl->setSummaryColumns(mdl->baseRec.indexOf("sum"));

    }

    return true;
}
