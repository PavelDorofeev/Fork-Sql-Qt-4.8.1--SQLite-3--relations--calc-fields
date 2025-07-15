#ifndef QP_COMBOBOX_H
#define QP_COMBOBOX_H

#include <QComboBox>
#include <QMouseEvent>
class Qp_TreeItem_2;

#include "qp/gui/dll_qp_gui_global.h"

class LIB_PREFIX_QP_GUI QpComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit QpComboBox(QWidget *parent = 0);

    void paintEvent(QPaintEvent *e);
    
    virtual void mousePressEvent(QMouseEvent *);

    bool commitData( const QVariant & );

    void wheelEvent(QWheelEvent *event);

    Qp_TreeItem_2* treeItem;

signals:


public Q_SLOTS:

    void slot_dataChanged_2( const QVariant & newVal);

signals:
    void sig_commitData(const QVariant &);
    
public slots:
    
};

#endif // QP_COMBOBOX_H
