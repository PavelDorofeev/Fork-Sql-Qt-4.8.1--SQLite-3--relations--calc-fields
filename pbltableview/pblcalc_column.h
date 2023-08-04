#ifndef PBLCALC_COLUMN_H
#define PBLCALC_COLUMN_H

#include <QString>

const class PblCalcColumn
{
public:

    PblCalcColumn();

    explicit PblCalcColumn( const QString &summaryField,

                            const QString &extTblName,

                            const QString &idField1Name,

                            const QString &idField2Name,

                            const QString &calcFunc,

                            const QString &header=QString(),

                            const QString &col_after = QString()
            );

    PblCalcColumn &operator=(const PblCalcColumn& other);

    const QString     summaryField;

    const QString     extTblName;

    const QString     idField1Name;

    const QString     idField2Name;

    const QString     calcFunc;

    const QString   col_after;


    const QString   header;

    const QString   select_as_name;

    QString  get_fld_name();


};

#endif // PBLCALC_COLUMN_H
