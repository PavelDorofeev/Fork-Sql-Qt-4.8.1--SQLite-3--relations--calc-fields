#ifndef QP_SUBACCNT_H
#define QP_SUBACCNT_H

#include <QString>

class QpSubAccnt
{
public:

    QpSubAccnt();

    explicit QpSubAccnt( const QString &extTblName,
                          const QString & fld1,
                          const QString & fld2,
                          const QString & sub_on_fld_name_extTbl
                          );

    QpSubAccnt operator=(const QpSubAccnt &other); // !!!

    const QString extTblName;
    const QString fld1;
    const QString fld2;
    const QString sub_on_fld_name_extTbl;

    QString get_sub_on_fld_name() const;

};

#endif // QP_SUBACCNT_H
