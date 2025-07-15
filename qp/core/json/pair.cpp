#include "pair.h"

Pair2::Pair2()
    :
      key(""),
      val("")
{

}

Pair2::Pair2(const QString& Key , const QVariant & Value)
    :
      key( Key ),
      val ( Value )

{

}


