#ifndef PBLCALC_COLUMN_H
#define PBLCALC_COLUMN_H

#include <QString>

typedef struct CALC_COLUMN
{
    CALC_COLUMN():
        extTblName(QString()),
        idField1(-1),
        idField2Name(QString()),
        summaryField(QString()),
        calcFunc(QString()),
        calcFuncName_As(QString()),
        col(-1)
    {

    }
    int col;
    QString     summaryField;

    QString     extTblName;

    int         idField1;

    QString     idField2Name;

    QString     calcFunc;

    QString     calcFuncName_As;
};


class PblCalcColumn
{
public:

    PblCalcColumn();

    PblCalcColumn(const CALC_COLUMN & calc,
              int col);

    int col;

    int extCol;

    CALC_COLUMN calc;


};

#endif // PBLCALC_COLUMN_H
