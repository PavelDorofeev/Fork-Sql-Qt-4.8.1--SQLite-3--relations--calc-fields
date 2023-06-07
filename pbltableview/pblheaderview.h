#ifndef PBLHEADERVIEW_H
#define PBLHEADERVIEW_H

#include <QHeaderView>

class PblHeaderView : public QHeaderView
{
    Q_OBJECT
public:
    explicit PblHeaderView(Qt::Orientation orientation, QWidget *parent = 0);
    

    void PblHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;

    QSize sizeHint() const;

signals:
    
public slots:
    
};

#endif // PBLHEADERVIEW_H
