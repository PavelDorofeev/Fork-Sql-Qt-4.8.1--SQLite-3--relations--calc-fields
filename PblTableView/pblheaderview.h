#ifndef PBLHEADERVIEW_H
#define PBLHEADERVIEW_H

#include <QHeaderView>

class PblSqlRelationalTableModel;

class PblHeaderView : public QHeaderView
{
    Q_OBJECT
public:
    explicit PblHeaderView(PblSqlRelationalTableModel * mdl, Qt::Orientation orientation, QWidget *parent = 0);
    
    void paintEvent(QPaintEvent *e);
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;


    PblSqlRelationalTableModel * mdl;
signals:
    
public slots:
    
};

#endif // PBLHEADERVIEW_H
