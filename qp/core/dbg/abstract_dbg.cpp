#include "abstract_dbg.h"

ADbg::ADbg():lvl(1)

{
}

//QString ADbg::fullInfo() const
//{
//    return "\n";
//}

QDebug operator<<(QDebug d, const ADbg& st)
{
    d << st.fullInfo();

    return d;
}


