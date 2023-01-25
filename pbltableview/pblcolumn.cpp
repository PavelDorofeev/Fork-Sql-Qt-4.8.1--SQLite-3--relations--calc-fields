#include "pblcolumn.h"

PblColumn::PblColumn()
{
    //qDebug() << "ctor ExColumns";
}

PblColumn::PblColumn(const PblSqlRelation &relation,
                     int exCol_)
    :
    ext_table(relation.ext_table),
    idField1(relation.idField1),
    idField2(relation.idField2),
    destField(relation.destField),
    type(COLUMN_TYPE_RELATION_ID)
{
    origCol = relation.col;
    exCol = exCol_;

}

PblColumn::PblColumn(CALC_COLUMN & calc , int col_ )
{
    ext_table = calc.table;
    idField1 = calc.idField1;
    idField2 = calc.idField2;
    destField = calc.summaryField;
    funcName = calc.calcFunc;
    renamedField_As  = calc.calcFuncName_As;
    exCol = col_;

    type = COLUMN_TYPE_CALCULATION;
}

bool PblColumn::isValid()
{
    if( ! ext_table.isEmpty()
            && idField1 != -1
            && ! destField.isEmpty())
        return true;

    return false;
}
