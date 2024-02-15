#ifndef QP_COLUMNINFO_H
#define QP_COLUMNINFO_H

#include <QSqlTableModel>
#include <QDebug>

class QpColumnInfo
{
public:

    QpColumnInfo();

    explicit QpColumnInfo( const Qt::Alignment Alignment,
                          const int Precision);

    Qt::Alignment alignment;
    int precision;
    char cFormat;
    bool editable;
    bool selectable;
    bool is_visible;
    QString header;

};

#ifndef QT_NO_DEBUG_STREAM
    Q_SQL_EXPORT QDebug operator<<(QDebug, const QpColumnInfo &);
#endif

#endif // QP_COLUMNINFO_H
