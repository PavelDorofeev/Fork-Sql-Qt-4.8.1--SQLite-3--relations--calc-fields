#ifndef HORIZONTAL_HEADER_H
#define HORIZONTAL_HEADER_H

#include <QHeaderView>
#include "qp/tableview/qp_horheaderview.h"
#include <QMouseEvent>

class Horizontal_Header : public QpHorHeaderView
{
    Q_OBJECT
public:
    explicit Horizontal_Header(QpTableView *parent);

    ~Horizontal_Header();

    //void initialize_Sections();

    
protected:
        virtual void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void sig_needsReselect(QList<int>);
    
public slots:

private slots:
    void slot_sectionPressed(int section);

private:
    int lastPressedSection;
    
};

#endif // HORIZONTAL_HEADER_H
