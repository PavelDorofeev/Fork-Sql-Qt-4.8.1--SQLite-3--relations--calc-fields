#ifndef QP_SQLRECORD_H
#define QP_SQLRECORD_H

#include <QSqlRecord>
#include <QHash>

class QpSqlTableModel;

class QpSqlRecord : public QSqlRecord
{

public:

    typedef enum SPECIAL_FLD_TYPES{
        //RELATION_TXT_FLD=1,
        RELATION_ID_EXT_FLD=1,
        SUBACCOUNT_ENABLE_FLD,
        CALC_FLD
    };

    QpSqlRecord();

    explicit QpSqlRecord( QpSqlTableModel &mdl ,
                           const QSqlRecord &rec); // copy ctor

    QpSqlRecord& operator=(const QSqlRecord& other);

    virtual ~QpSqlRecord();

    QHash< QString, SPECIAL_FLD_TYPES > specialFld;


    int getRelIdCol(const QString& relCol) const;

private:

    void func1(const QSqlRecord &rec);

    QpSqlTableModel *mdl;


};

#endif // QP_SQLRECORD_H
