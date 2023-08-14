#ifndef PBLSQLRECORD_H
#define PBLSQLRECORD_H

#include <QSqlRecord>
#include <QHash>

//#include "pblsqlrelationaltablemodel.h"
class PblSqlRelationalTableModel;

class PblSqlRecord : public QSqlRecord
{

public:

    typedef enum SPECIAL_FLD_TYPES{
        //RELATION_TXT_FLD=1,
        RELATION_ID_EXT_FLD=1,
        SUBACCOUNT_ENABLE_FLD,
        CALC_FLD
    };

    PblSqlRecord();

    explicit PblSqlRecord( PblSqlRelationalTableModel &mdl ,
                           const QSqlRecord &rec); // copy ctor

    PblSqlRecord& operator=(const QSqlRecord& other);

    virtual ~PblSqlRecord();

    //int priCol;

    QHash< QString, SPECIAL_FLD_TYPES > specialFld;

    //QHash< QString, QString > relFields;

    int getRelIdCol(const QString& relCol) const;

private:

    void func1(const QSqlRecord &rec);

    PblSqlRelationalTableModel *mdl;


};

#endif // PBLSQLRECORD_H
