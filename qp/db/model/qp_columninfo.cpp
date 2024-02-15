#include "qp_columninfo.h"

QpColumnInfo::QpColumnInfo()
    :
      alignment(Qt::AlignCenter),
      precision(0),
      cFormat(' '),
      editable(true),
      selectable(false), // true = only for realtional fields, this will be calls a Dialog for selecting
      is_visible( true ),
      header(QString())
{

}

QpColumnInfo::QpColumnInfo( const Qt::Alignment Alignment,
                              const int Precision)
    :
      alignment(Alignment),
      precision(Precision),
      cFormat(' '),
      editable(true),
      selectable(false), // true = only for realtional fields, this will be calls a Dialog for selecting
      is_visible( true )
{

}


#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const QpColumnInfo &inf)
{
    dbg << "COLUMN_INFO";
    dbg << "\n  alignment: " << QString("%1").arg(inf.alignment);
    dbg << "\n  is_visible: " << QString("%1").arg(inf.is_visible);
    dbg << "\n  editable: " << QString("%1").arg(inf.editable);
    return dbg;
}
#endif
