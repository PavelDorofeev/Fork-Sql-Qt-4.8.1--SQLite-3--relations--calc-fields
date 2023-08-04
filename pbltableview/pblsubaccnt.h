#ifndef PBLSUBACCNT_H
#define PBLSUBACCNT_H

#include <QString>

class PblSubAccnt
{
public:

    PblSubAccnt();

    explicit PblSubAccnt( const QString &extTblName,
                          const QString & fld1,
                          const QString & fld2,
                          const QString & sub_on_fld_name_extTbl
                          );

    PblSubAccnt operator=(const PblSubAccnt &other); // !!!

    const QString extTblName;
    const QString fld1;
    const QString fld2;
    const QString sub_on_fld_name_extTbl;

    QString get_sub_on_fld_name() const;

};

#endif // PBLSUBACCNT_H
