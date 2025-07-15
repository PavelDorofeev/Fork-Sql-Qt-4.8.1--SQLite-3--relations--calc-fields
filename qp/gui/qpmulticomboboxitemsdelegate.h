#ifndef QPMULTICOMBOBOXITEMSDELEGATE_H
#define QPMULTICOMBOBOXITEMSDELEGATE_H

#include <QStyledItemDelegate>
#include <QEvent>
#include <QEvent>

#include "qp/gui/dll_qp_gui_global.h"
class LIB_PREFIX_QP_GUI QpMultiComboBoxItemsDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    QpMultiComboBoxItemsDelegate( QWidget *parent);

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const    QModelIndex &index) const;


    bool editorEvent(QEvent *event, QAbstractItemModel *model,
                     const QStyleOptionViewItem &option, const QModelIndex &index);

    bool toggleChecked( QAbstractItemModel *model, const QModelIndex &index);

    int checkedBitsNumber( QAbstractItemModel *model)  const ;

    int checkedBitsLimit;

    void  setAllCheckedToNone( QAbstractItemModel *model );

    //void setEditorData(QWidget *editor, const QModelIndex &index) const;

    //bool eventFilter(QObject *object, QEvent *event);
signals:

    void sig_something_changed();

private:
    QWidget * prnt;

};

#endif // QPMULTICOMBOBOXITEMSDELEGATE_H
