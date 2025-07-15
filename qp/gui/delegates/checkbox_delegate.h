#ifndef CHECKBOX_DELEGATE_H
#define CHECKBOX_DELEGATE_H

#include <QStyledItemDelegate>
#include <QCheckBox>

#include <QSvgRenderer>
#include <QAbstractTableModel>

//class QpSqlTableModel;
//class QpTableViewWrapper;

#include "qp/gui/dll_qp_gui_global.h"
class LIB_PREFIX_QP_GUI checkBox_Delegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit checkBox_Delegate( QWidget *parent = 0);

    ~checkBox_Delegate();
    


    QWidget* createEditor(QWidget* parent,
                          const QStyleOptionViewItem& option,
                          const QModelIndex& index) const;

    void paint(QPainter *painter,
                  const QStyleOptionViewItem &option,
                  const QModelIndex &index) const;

signals:

public slots:

private:
    QAbstractTableModel * mdl;
    //QpTableViewWrapper * view;

    QSvgRenderer *svg_renderer;
    QSvgRenderer *svg_renderer_inv;

    int m_margin;

    int em1H;
};

#endif // CHECKBOX_DELEGATE_H
