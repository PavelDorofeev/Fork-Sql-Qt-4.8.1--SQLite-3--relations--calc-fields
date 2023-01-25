#ifndef PBLCOLUMN_H
#define PBLCOLUMN_H

#include <QString>
//#include "pblsqlrelationaltablemodel.h"
#include "pblsqlrelation.h"

typedef struct CALC_COLUMN
{
    CALC_COLUMN():
        table(QString()),
        idField1(-1),
        idField2(QString()),
        summaryField(QString()),
        calcFunc(QString()),
        calcFuncName_As(QString())
    {

    }

    QString     summaryField;
    QString     table;
    int         idField1;
    QString     idField2;
    QString     calcFunc;
    QString     calcFuncName_As;
};

class PblColumn
{

public:
    enum COLUMN_TYPE
    {
        COLUMN_TYPE_UNKNOUWN=-1,
        COLUMN_TYPE_RELATION_TEXT = 1,
        COLUMN_TYPE_RELATION_ID = 2,
        COLUMN_TYPE_CALCULATION = 3
    };

    PblColumn();

    PblColumn(CALC_COLUMN & calc,
              int col);

    PblColumn(const PblSqlRelation &relation,
              int exCol);

    int origCol;
    int exCol;

    COLUMN_TYPE type;

    QString ext_table;
    int     idField1;
    QString idField2;
    QString destField;
    QString funcName;
    QString renamedField_As;

    bool isValid();



private:


};


#endif // PBLCOLUMN_H
