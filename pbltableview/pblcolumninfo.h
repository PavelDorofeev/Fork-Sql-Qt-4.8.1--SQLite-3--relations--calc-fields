#ifndef PBLCOLUMNINFO_H
#define PBLCOLUMNINFO_H

#include <QSqlTableModel>
#include <QDebug>

class PblColumnInfo
{
public:

    PblColumnInfo();

    explicit PblColumnInfo( const Qt::Alignment Alignment,
                          const int Precision);

    Qt::Alignment alignment;
    int precision;
    char cFormat;
    bool editable;
    bool selectable;
    bool is_visible;

};

#ifndef QT_NO_DEBUG_STREAM
    Q_SQL_EXPORT QDebug operator<<(QDebug, const PblColumnInfo &);
#endif

#endif // COLUMNINFO_H
