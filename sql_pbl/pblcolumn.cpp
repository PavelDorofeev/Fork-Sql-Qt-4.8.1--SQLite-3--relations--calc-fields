#include "pblcolumn.h"

PblColumn::PblColumn()
{
    //qDebug() << "ctor ExColumns";
}

PblColumn::PblColumn(COLUMN_TYPE rel_Type,
                     const QString &exTableName_,
                     const QString &exIndexField_,
                     const QString &exTextField_,
                     const QString &funcName,
                     int origCol_,
                     int exCol_,

                     const QString renamedField_As_):
    exTableName(exTableName_),
    exIndexFieldName(exIndexField_),
    exTextFieldName(exTextField_),
    exFuncName(funcName),
    renamedField_As(renamedField_As_),
    cFormat(0),
    precision(0),
    alignment(Qt::AlignRight)
{
    type = rel_Type;
    origCol = origCol_;
    exCol = exCol_;

}

bool PblColumn::isValid()
{
    if( ! exTableName.isEmpty()
            && ! exIndexFieldName.isEmpty()
            && ! exTextFieldName.isEmpty())
        return true;

    return false;
}
