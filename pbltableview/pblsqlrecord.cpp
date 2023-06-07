#include "pblsqlrecord.h"
#include <QDebug>

PblSqlRecord::PblSqlRecord(const QSqlRecord &rec)
    :
      QSqlRecord(rec),
      priCol(-1)
{

    qDebug() << "PblSqlRecord rec " << rec;
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
