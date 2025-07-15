#ifndef DEFAULTSTYLEDITEMDELEGATE_H
#define DEFAULTSTYLEDITEMDELEGATE_H

#include <QStyledItemDelegate>

class QpSqlTableModel;

#include "qp/gui/dll_qp_gui_global.h"
class LIB_PREFIX_QP_GUI DefaultStyledItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit DefaultStyledItemDelegate( QObject *parent = 0);
    

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const;

    //QString displayText(const QVariant &value, const QLocale &locale) const ;

//    QSize sizeHint(const QStyleOptionViewItem &option,
//                   const QModelIndex &index) const;

signals:
    
public slots:

private:
    
};

#endif // DEFAULTSTYLEDITEMDELEGATE_H
