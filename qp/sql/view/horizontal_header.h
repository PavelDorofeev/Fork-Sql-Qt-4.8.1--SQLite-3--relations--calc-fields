#ifndef HORIZONTAL_HEADER_H
#define HORIZONTAL_HEADER_H

#include <QHeaderView>
#include "qp/sql/tableview/qp_horheaderview.h"
#include <QMouseEvent>

#include "qp/sql/dll_qp_sql_global.h"
class LIB_PREFIX_QP_SQL Horizontal_Header : public QHeaderView
{
    Q_OBJECT
public:
    explicit Horizontal_Header(QWidget *parent);

    ~Horizontal_Header();

    //void initialize_Sections();

    void resizeSections(QHeaderView::ResizeMode mode);
    
protected:
        virtual void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void slot_sectionPressed(int section);

signals:
    void sig_needsReselect(QList<int>);
    
public slots:

private slots:

private:
    int lastPressedSection;
    
};

#endif // HORIZONTAL_HEADER_H
