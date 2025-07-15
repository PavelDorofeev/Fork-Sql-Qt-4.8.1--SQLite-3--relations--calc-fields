#ifndef EMPTY_DELEGATE_H
#define EMPTY_DELEGATE_H

#include <QStyledItemDelegate>

#include "qp/gui/dll_qp_gui_global.h"
class LIB_PREFIX_QP_GUI Empty_Delegate : public QStyledItemDelegate
{
public:
    Empty_Delegate(QWidget *parent);

        QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;

    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;
};

#endif // EMPTY_DELEGATE_H
