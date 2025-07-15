#ifndef QP_RELATIONDELEGATE_H
#define QP_RELATIONDELEGATE_H

#include <QStyledItemDelegate>


class QSvgRenderer;

#include "qp/gui/dll_qp_gui_global.h"
class LIB_PREFIX_QP_GUI QpRelationDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit QpRelationDelegate(QWidget *parent = 0);
    
    QString displayText(const QVariant &value, const QLocale &locale) const;

    void paint( QPainter *painter,
                const QStyleOptionViewItem &option,
                const QModelIndex &index) const;


    QSvgRenderer *svg_renderer;

protected:

//    void drawDisplay ( QPainter * painter, const QStyleOptionViewItem & option, const QRect & rect, const QString & text ) const;

signals:

public slots:

private:

    int maxIconSz;

};

#endif // QPRELATIONDELEGATE_H
