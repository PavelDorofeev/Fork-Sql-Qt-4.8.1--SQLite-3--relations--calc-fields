#include "pblcalc_column.h"
#include <QDebug>

PblCalcColumn::PblCalcColumn()
{
    qDebug() << "ctor default PblCalcCol";

    //Q_ASSERT( 1==0 );
}

PblCalcColumn::PblCalcColumn(const CALC_COLUMN & Calc , int ExCol )
    :
      calc(Calc)
{
    //qDebug() << "ctor PblCalcCol";

    col = calc.col;

    extCol = ExCol;

}
