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

        mdl->setDependColumn(mdl->fieldIndex("price"),
                            mdl->fieldIndex("sum"),
                            PblSqlRelationalTableModel2::MULTI,
                            mdl->fieldIndex("qty")
                            );


        mdl->setDependColumn( mdl->fieldIndex("qty"),
                            mdl->fieldIndex("sum"),
                            PblSqlRelationalTableModel2::MULTI,
                            mdl->fieldIndex("price")
                            );

        mdl->setSummaryColumns(mdl->fieldIndex("sum"));

    }

    return true;
}
