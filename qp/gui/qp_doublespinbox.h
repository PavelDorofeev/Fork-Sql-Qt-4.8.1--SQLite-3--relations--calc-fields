#ifndef QPDOUBLESPINBOX_H
#define QPDOUBLESPINBOX_H

#include <QDoubleSpinBox>
#include <QWheelEvent>
#include <QAbstractItemModel>
#include <QModelIndex>

typedef bool (*cb_test_double_value_func2) ( double newVal );

class Qp_TreeItem_2;

#include "qp/gui/dll_qp_gui_global.h"

class LIB_PREFIX_QP_GUI QpDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    explicit QpDoubleSpinBox(QWidget *parent = 0,
                             cb_test_double_value_func2 cb_test_double_value_func2 =0);

    Qp_TreeItem_2 *treeItem;

    void wheelEvent(QWheelEvent *event);


    double valueFromText(const QString &text) const;

    QValidator::State validate(QString &input, int &pos) const;

    void mousePressEvent(QMouseEvent *event);
    void changeEvent(QEvent *event);

signals:
    
public Q_SLOTS:

    void setValue(double val);

private:
    cb_test_double_value_func2 cb_test_double_value2;
    
};

#endif // QPDOUBLESPINBOX_H
