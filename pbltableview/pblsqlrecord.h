#ifndef PBLSQLRECORD_H
#define PBLSQLRECORD_H

#include <QSqlRecord>
#include <QHash>

class PblSqlRecord : public QSqlRecord
{
public:

    PblSqlRecord()
    {
    }

    explicit PblSqlRecord(const QSqlRecord &rec);

    virtual ~PblSqlRecord();

    int priCol;

    QHash<int, int> hash;

    int getRelIdColumn(int relCol) const;


};

#endif // PBLSQLRECORD_H
