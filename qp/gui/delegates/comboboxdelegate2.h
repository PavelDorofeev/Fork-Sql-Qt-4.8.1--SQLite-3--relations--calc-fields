#ifndef COMBOBOXDELEGATE2_H
#define COMBOBOXDELEGATE2_H

#include <QStyledItemDelegate>

#include "qp/gui/dll_qp_gui_global.h"
class LIB_PREFIX_QP_GUI ComboBoxDelegate2 : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ComboBoxDelegate2( const QVariantList &Lst,
                                QWidget *parent = 0);

    explicit ComboBoxDelegate2( const QHash<int,QString> &Lst,
                                QWidget *parent = 0);
    
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;

    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;

    QString displayText(const QVariant &value, const QLocale &locale) const ;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;

signals:
    
public slots:

private:

    QList< QPair < int , QString > > pair_lst;

    QHash<int,int> hashLst;

    QWidget* parent_;
    
};

#endif // COMBOBOXDELEGATE2_H
