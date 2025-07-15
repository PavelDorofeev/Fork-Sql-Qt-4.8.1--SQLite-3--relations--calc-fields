#ifndef VERTICAL_HEADER_H
#define VERTICAL_HEADER_H

#include <QHeaderView>

#include "qp/sql/dll_qp_sql_global.h"
class LIB_PREFIX_QP_SQL Vertical_Header : public QHeaderView
{
    Q_OBJECT
public:
    explicit Vertical_Header(QWidget *parent = 0);
    
    //void resizeSections(QHeaderView::ResizeMode mode);

    //int sectionSizeHint( int logicalIndex );

    //int sectionSize(int logicalIndex) const;

signals:
    
public slots:
    
};

#endif // VERTICAL_HEADER_H
