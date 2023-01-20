#include "checkbox_delegate.h"
#include <QMouseEvent>
#include <QApplication>
#include <QDebug>
#include <QPainter>
#include <QPalette>

static QRect CheckBoxRect(const QStyleOptionViewItem &view_item_style_options)
{
    QStyleOptionButton check_box_style_option;

    QRect check_box_rect = QApplication::style()->subElementRect(QStyle::SE_CheckBoxIndicator,&check_box_style_option);

    QPoint check_box_point(view_item_style_options.rect.x() + view_item_style_options.rect.width() / 2 -
                           check_box_rect.width() / 2,
                           view_item_style_options.rect.y() +
                           view_item_style_options.rect.height() / 2 -
                           check_box_rect.height() / 2);

    return QRect(check_box_point, check_box_rect.size());
}

checkBox_Delegate::~checkBox_Delegate()
{
    qDebug("~checkBox_Delegate");
}

QWidget *checkBox_Delegate::createEditor(QWidget *parent,
                                         const QStyleOptionViewItem &option,
                                         const QModelIndex &index) const
{
    return 0;
}

checkBox_Delegate::checkBox_Delegate(PblSqlRelationalTableModel * Mdl,
                                     QWidget *parent) :
    QStyledItemDelegate(parent)
{
    mdl = Mdl;
}

void checkBox_Delegate::paint(QPainter *painter,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const
{
    //qDebug() << QString("checkBox_Delegate::paint [%1x%2]").arg(index.row()).arg(index.column());

    bool checked = index.model()->data(index, Qt::DisplayRole).toBool();


    QStyleOptionButton check_box_style_option;

    check_box_style_option.state |= QStyle::State_Enabled;

    if (checked)
    {
        check_box_style_option.state |= QStyle::State_On;
    }
    else
    {
        check_box_style_option.state |= QStyle::State_Off;
    }

    check_box_style_option.rect = CheckBoxRect(option);

    painter->save();

    if(mdl->isSelectedLine != -1 && index.row() == mdl->isSelectedLine)
    {

        QStyleOptionViewItem newOpt = option;

        painter->setPen(QPen(newOpt.palette.color(QPalette::Text))); // Цвет пера

        painter->fillRect( newOpt.rect, QApplication::palette().color(QPalette::AlternateBase));

    }
    else
    {
        if (option.state & QStyle::State_Selected)
        {
            painter->setPen(QPen(option.palette.color(QPalette::HighlightedText))); // Цвет пера
            painter->fillRect(option.rect, option.palette.highlight());
        }

    }

    QApplication::style()->drawControl(QStyle::CE_CheckBox, &check_box_style_option, painter);

    painter->restore();

}


/*bool checkBox_Delegate::editorEvent(QEvent *event,
                                    QAbstractItemModel *model,
                                    const QStyleOptionViewItem &option,
                                    const QModelIndex &index)
{

    return QStyledItemDelegate::editorEvent(event, model , option , index);
}*/

