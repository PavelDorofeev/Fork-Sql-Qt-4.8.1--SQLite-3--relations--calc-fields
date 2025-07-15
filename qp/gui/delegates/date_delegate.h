#ifndef DATE_DELEGATE_H
#define DATE_DELEGATE_H

#include <QStyledItemDelegate>
#include <QDateEdit>

#include "qp/gui/dll_qp_gui_global.h"
class LIB_PREFIX_QP_GUI date_Delegate : public QStyledItemDelegate
{
public:
    date_Delegate(int fullDateTime=0, QWidget *parent=0);

    QWidget *date_Delegate::createEditor(QWidget *parent,
        const QStyleOptionViewItem &/* option */,
        const QModelIndex &/* index */) const;

    void setEditorData(QWidget *editor,const QModelIndex &index) const;

    void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const;

    QString date_Delegate::displayText(const QVariant &value, const QLocale &locale) const;

private:
    int fullDateTime_;
};

#endif // DATE_DELEGATE_H
