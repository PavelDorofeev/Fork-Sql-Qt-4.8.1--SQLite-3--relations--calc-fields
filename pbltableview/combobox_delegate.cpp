#include "combobox_delegate.h"
#include <QComboBox>
#include <QDebug>
#include "some_tests.h"
#include <QApplication>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QPalette>
#include <QApplication>

#include "pbltableview/pbltableview.h"

ComboBoxDelegate::ComboBoxDelegate(
        const QStringList &Lst,
        QWidget *parent)
    :
      QStyledItemDelegate(parent),

      lst(Lst)

{


}



QWidget *ComboBoxDelegate::createEditor(QWidget *parent,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const
{


    QComboBox *cmb = new QComboBox(parent);

    cmb->insertItems(0,lst);

    QPalette palette = option.palette; //editor->palette();

    cmb->setPalette(palette);

    return cmb;
}



void ComboBoxDelegate::setModelData(QWidget *editor,
                                    QAbstractItemModel *model,
                                    const QModelIndex &index) const
{

    QComboBox *edit = qobject_cast<QComboBox *>(editor);

    int newValue=edit->currentIndex();

    bool res = model->setData(index, newValue, Qt::EditRole);

}


QString ComboBoxDelegate::displayText(const QVariant &value,
                                      const QLocale &locale) const
{


    bool ok = false;
    int ii = value.toInt(&ok);

    if(ok)
    {
        if ( ii>=0 && ii <lst.count() )
        {
            return lst.at(ii);
        }
    }

    return "";

}

void ComboBoxDelegate::paint(QPainter *painter,
                             const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{


    QStyleOptionViewItemV4 opt1 = option;

    initStyleOption(&opt1, index); // !!! set opt1.text =...

    QStyle *style = QApplication::style();

    style->drawControl(QStyle::CE_ItemViewItem, &opt1, painter);

    //style->drawItemText(painter , opt1.rect);

    //painter->drawText( opt1.rect ,  opt1.text);

}


