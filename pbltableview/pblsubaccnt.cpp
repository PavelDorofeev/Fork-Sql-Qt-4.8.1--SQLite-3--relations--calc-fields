#include "pblsubaccnt.h"

PblSubAccnt::PblSubAccnt()
{

}

PblSubAccnt::PblSubAccnt( const QString & ExtTblName,
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

PblSubAccnt PblSubAccnt::operator=(const PblSubAccnt &other)
{
    return *this;
};


QString PblSubAccnt::get_sub_on_fld_name() const
{
    return QString("%1_%2")
            .arg(extTblName)
            .arg(sub_on_fld_name_extTbl)
            ;
}
