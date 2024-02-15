#ifndef QP_CALC_COLUMN_H
#define QP_CALC_COLUMN_H

#include <QString>

const class QpCalcColumn
{
public:

    QpCalcColumn();

    explicit QpCalcColumn( const QString &summaryField, // sql operation as field name( for sum,count)

                            const QString &extTblName, // external table name from which calculate values

                            const QString &idField1Name, //  innner field id name

                            const QString &idField2Name, //  external field id name

                            const QString &calcFunc,    // sql calculation name

                            const QString &header=QString(), // header for result column

                            const QString &col_after = QString()
            );

    QpCalcColumn &operator=(const QpCalcColumn& other);

    const QString     summaryField;

    const QString     extTblName;

    const QString     idField1Name;

    const QString     idField2Name;

    const QString     calcFunc;

    const QString   col_after;


    const QString   header;

    QString   select_as_name;

    QString  get_fld_name();


};

#endif // QP_CALC_COLUMN_H
