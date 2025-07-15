#include "qprelationdelegate.h"

#include <QSvgRenderer>
#include <QPainter>
#include <QFontMetrics>
#include <QApplication>
#include <QItemDelegate>
#include <QDebug>

QpRelationDelegate::QpRelationDelegate(QWidget *parent) :
    QStyledItemDelegate(parent)
{
    svg_renderer = new QSvgRenderer( QString(":view/img/btn-db/ext_table_select.svg") , this);



    QFontMetrics mm( QApplication::font() );
    maxIconSz =  mm.height();

//    qDebug() << "mm.height()" << mm.height();
//    qDebug() << "mm.averageCharWidth()" << mm.averageCharWidth();
}



QString QpRelationDelegate::displayText(const QVariant &value, const QLocale &locale) const
{
    //value.toDateTime()

    //qDebug() << "value " <<value.toString();
    //qDebug() << "dt.fromTime_t " << dt.toString("yyyy-MM-dd HH:MM:ss");

//    qDebug() << "QpRelationDelegate::displayText" << value.toString();
    return value.toString();

}

//void QpRelationDelegate::drawDisplay ( QPainter * painter, const QStyleOptionViewItem & option, const QRect & rect, const QString & text ) const
//{
//    QStyleOptionViewItem opt = option;
//    opt.displayAlignment |= Qt::AlignRight;
//    QItemDelegate::drawDisplay ( painter, opt, rect, text);
//}


void QpRelationDelegate::paint(QPainter *painter,
                               const QStyleOptionViewItem &option,
                               const QModelIndex &index) const
{

    QString text = index.model()->data(index, Qt::DisplayRole).toString();

    QStyleOptionButton opt;

    painter->save();

    QStyleOptionViewItemV4 opt1 = option;

    QRect rect1 ( opt1.rect.x(),
                  opt1.rect.y(),
                  opt1.rect.width() - opt1.rect.height(),
                  opt1.rect.height());

    //    QStyleOptionViewItem alignedOption(option);
    //    alignedOption.displayAlignment = Qt::AlignRight;

    //    QStyledItemDelegate::paint(painter, alignedOption, index);

    //    return;

    Q_ASSERT(index.isValid());


    initStyleOption(&opt1, index);

    //    opt1.viewItemPosition = QStyleOptionViewItemV4::Middle;
    //    opt1.features = QStyleOptionViewItemV2::WrapText;
    //    opt1.displayAlignment = Qt::AlignRight;
    //    opt1.decorationPosition = QStyleOptionViewItem::Bottom;

    int hh = qMin ( maxIconSz , opt1.rect.height() );

    QRect rectT = opt1.rect;
    rectT.setRight( opt1.rect.right() - hh );

    painter->drawText( rectT , Qt::AlignVCenter|Qt::AlignLeft|Qt::TextWordWrap, text);

    int yy = (opt1.rect.height() - hh ) / 2 ;


    QRect rect2 ( opt1.rect.x() + opt1.rect.width() - hh,
                  opt1.rect.y() + yy, // координата y
                  hh, //
                  hh );

    svg_renderer->render( painter , rect2);


    painter->restore();

}
