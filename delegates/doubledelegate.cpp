#include "doubledelegate.h"
//#include <QAbstractItemView>
#include <QPainter>
#include <QDebug>
#include <QDoubleSpinBox>


DoubleDelegate::DoubleDelegate(int Precision,
                               QObject *parent)
    :
    QStyledItemDelegate(parent)
    ,precision(Precision)
{

}

void DoubleDelegate::paint(QPainter *painter,
                           const QStyleOptionViewItem &option,
                           const QModelIndex &index) const
{


    QStyledItemDelegate::paint(painter, option, index);
}


QWidget *DoubleDelegate::createEditor( QWidget *parent,
                                      const QStyleOptionViewItem &option,
                                      const QModelIndex &index) const
{

    QDoubleSpinBox *spnBx = new QDoubleSpinBox(parent);

    spnBx->setDecimals( precision );

    QPalette palette = option.palette;

    spnBx->setPalette(palette);

    return spnBx;
}
