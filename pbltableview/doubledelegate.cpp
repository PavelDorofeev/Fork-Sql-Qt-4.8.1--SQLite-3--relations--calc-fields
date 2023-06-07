#include "doubledelegate.h"
#include <QAbstractItemView>
#include <QPainter>
#include <QDebug>
#include <QDoubleSpinBox>
#include "pbltableview.h"


DoubleDelegate::DoubleDelegate(PblSqlRelationalTableModel *mdl_, QObject *parent) :
    QStyledItemDelegate(parent)
{

    mdl =mdl_;
}

void DoubleDelegate::paint(QPainter *painter,
                           const QStyleOptionViewItem &option,
                           const QModelIndex &index) const
{

    QAbstractItemView* item = qobject_cast<QAbstractItemView*>(this->parent());
    //QStyledItemDelegate* tableView = qobject_cast<QStyledItemDelegate*>(this->parent());



    QStyledItemDelegate::paint(painter, option, index);
}


QWidget *DoubleDelegate::createEditor(QWidget *parent,
                                      const QStyleOptionViewItem &option,
                                      const QModelIndex &index) const
{
    int pr=2;

    if(index.isValid())
    {
        int col = index.column();

        if( mdl->colInfo.contains(col))
        {
            pr = mdl->colInfo.value(col).precision;
        }
    }

    QDoubleSpinBox *spnBx = new QDoubleSpinBox(parent);

    spnBx->setDecimals(pr);

    QPalette palette = option.palette;//editor->palette();

    spnBx->setPalette(palette);

    return spnBx;
}
