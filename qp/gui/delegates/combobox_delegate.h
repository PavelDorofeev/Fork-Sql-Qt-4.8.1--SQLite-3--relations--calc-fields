#ifndef COMBOBOX_DELEGATE_H
#define COMBOBOX_DELEGATE_H

#include <QStyledItemDelegate>
#include <QComboBox>
#include <QItemDelegate>

#include "qp/gui/dll_qp_gui_global.h"
class LIB_PREFIX_QP_GUI ComboBoxDelegate  : public QStyledItemDelegate
{
    Q_OBJECT
public:


    explicit ComboBoxDelegate( const QStringList &lst,
                               QWidget *parent);


    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;

    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;



    QString displayText(const QVariant &value, const QLocale &locale) const ;


protected:

public slots:

private slots:


private:

    QStringList lst;
    QComboBox *cmb;
    QWidget* parent_;

};


#endif // COMBOBOX_DELEGATE_H
