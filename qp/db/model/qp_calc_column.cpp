#include "qp_calc_column.h"

#include <QDebug>

QpCalcColumn::QpCalcColumn()
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


}

QpCalcColumn::QpCalcColumn( const QString &SummaryField,

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
      header(Header)


{

    //QString select_as_name1 = select_as_name.replace(',',"_");

    select_as_name = summaryField;
    select_as_name.replace( "," , "_" );


    //qDebug() << "summaryField " <<summaryField ;
    //qDebug() << "select_as_name " <<select_as_name ;
    //qDebug() << "select_as_name " <<select_as_name ;

    //select_as_name = QString("%1_%2_%3").arg(ExtTblName).arg(CalcFunc).arg(str);


}

QString QpCalcColumn::get_fld_name()
{
    return select_as_name;
}



QpCalcColumn& QpCalcColumn::operator=(const QpCalcColumn& other)
{

    //qDebug() << "PblCalcColumn::operator= " <<other.d;

    return *this;
}
