#include "pblcalc_column.h"

#include <QDebug>

PblCalcColumn::PblCalcColumn()
    :
      summaryField(QString()),
      extTblName(QString()),
      idField1Name(QString()),
      idField2Name(QString()),
      calcFunc(QString()),
      col_after(QString()),
      header(QString())
{
    qDebug() << "ctor default PblCalcCol";

    //Q_ASSERT( 1==0 );
}

PblCalcColumn::PblCalcColumn(const QString &SummaryField,

                             const QString &ExtTblName,

                             const QString &IdField1Name,

                             const QString &IdField2Name,

                             const QString &CalcFunc,

                             const QString &Header,

                             const QString &Col_after)

    :

      summaryField(SummaryField),
      extTblName(ExtTblName),
      idField1Name(IdField1Name),
      idField2Name(IdField2Name),
      calcFunc(CalcFunc),
      col_after(Col_after),
      header(Header),

      select_as_name(
          QString("%1_%2_%3")
          .arg(ExtTblName)
          .arg(CalcFunc)
          .arg(SummaryField)
          )
{


}

QString PblCalcColumn::get_fld_name()
{
    return select_as_name;
}



PblCalcColumn& PblCalcColumn::operator=(const PblCalcColumn& other)
{

    //qDebug() << "PblCalcColumn::operator= " <<other.d;

    return *this;
}
