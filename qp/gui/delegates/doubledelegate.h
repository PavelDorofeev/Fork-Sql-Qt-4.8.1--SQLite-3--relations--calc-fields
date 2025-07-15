#ifndef DOUBLEDELEGATE_H
#define DOUBLEDELEGATE_H

#include <QStyledItemDelegate>
//#include <QDoubleSpinBox>
#include "qp/qp.h"

typedef bool (*cb_test_double_value_func) (QAbstractItemModel *mdl, const QModelIndex &, double newVal);

#include "qp/gui/dll_qp_gui_global.h"
class LIB_PREFIX_QP_GUI DoubleDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:

    explicit DoubleDelegate( int Precision,
                             double Max ,
                             double Min = 0,
                             cb_test_double_value_func cb_Test_double_value =0 ,
                             QAbstractItemModel *mdl=0,
                             QWidget *parent = 0);

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;

    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;

    bool cb_valueChanged(double dd);

signals:
    
public slots:

private slots:
    void slot_valueChanged(double dd);

private:
    int precision;
    double min;
    double max;

    cb_test_double_value_func cb_test_double_value;

    QAbstractItemModel *mdl;
    mutable QModelIndex idx;


};

#endif // DOUBLEDELEGATE_H
