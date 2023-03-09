#include "pblsqlrecord.h"

PblSqlRecord::PblSqlRecord(const QSqlRecord &rec)
    :
      QSqlRecord(rec),
      priCol(-1)
{


}


PblSqlRecord::~PblSqlRecord()
{

}

int PblSqlRecord::getRelIdColumn(int relCol) const
{
    if( ! hash.contains(relCol))
        return -1;

    return hash.value(relCol);

}
