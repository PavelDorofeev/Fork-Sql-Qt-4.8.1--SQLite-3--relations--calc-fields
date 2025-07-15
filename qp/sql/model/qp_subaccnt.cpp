#include "qp_subaccnt.h"

QpSubAccnt::QpSubAccnt()
{

}

QpSubAccnt::QpSubAccnt( const QString & ExtTblName,
                          const QString & Fld1,
                          const QString & Fld2,
                          const QString & Sub_on_fld_name)
    :
      sub_on_fld_name_extTbl(Sub_on_fld_name),
      fld1(Fld1),
      fld2(Fld2),
      extTblName(ExtTblName)

{

}

QpSubAccnt QpSubAccnt::operator=(const QpSubAccnt &other)
{
    return *this;
};


QString QpSubAccnt::get_sub_on_fld_name() const
{
    return QString("%1_%2")
            .arg(extTblName)
            .arg(sub_on_fld_name_extTbl)
            ;
}
