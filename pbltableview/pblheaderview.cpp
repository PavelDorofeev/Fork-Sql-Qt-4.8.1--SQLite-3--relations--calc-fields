#include "pblheaderview.h"
#include <QDebug>

PblHeaderView::PblHeaderView(Qt::Orientation orientation, QWidget *parent) :
    QHeaderView( orientation , parent)
{

}


void PblHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{

    QRect rr = rect;

    //rr.adjust(30, 0, 10, 0);

    qDebug() << "PblHeaderView::paintSection logicalIndex " << logicalIndex;

    QHeaderView::paintSection(painter, rr, logicalIndex);
}


QSize PblHeaderView::sizeHint() const
{

    return QHeaderView::sizeHint();
}
