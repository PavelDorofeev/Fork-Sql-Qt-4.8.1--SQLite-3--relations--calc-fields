#ifndef PBLCOLUMN_H
#define PBLCOLUMN_H

#include <QString>
//#include "pblsqlrelationaltablemodel.h"
#include "pblsqlrelation.h"

class PblRelColumn
{

public:
    enum COLUMN_TYPE
    {
        COLUMN_TYPE_UNKNOUWN=-1,
        COLUMN_TYPE_RELATION_TEXT = 1,
        COLUMN_TYPE_RELATION_ID = 2,
        COLUMN_TYPE_CALCULATION = 3
    };

    PblRelColumn();

    PblRelColumn(const PblSqlRelation &relation,
              int exCol);

    PblRelColumn operator=(const PblRelColumn &other);

    int origCol;

    int exCol;

    //COLUMN_TYPE type;

    PblSqlRelation relation;

    const QString renamedHeaderCol;


private:


};


#endif // PBLCOLUMN_H
