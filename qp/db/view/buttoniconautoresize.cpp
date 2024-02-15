#include "buttoniconautoresize.h"

#include <QSize>
#include <QSizePolicy>
#include <QStylePainter>
#include <QStyleOptionButton>
#include <QtGlobal>
#include <QDebug>
#include <QApplication>

#include "qp/db/view/qp_tableview_wrapper.h"


ButtonIconAutoResize::ButtonIconAutoResize( QWidget *parent)
    : QToolButton( parent)
{

    QFont font = QApplication::font();

    QFontMetrics fm(font);

    //int ww = fm.width('w');
    int hh = fm.height();

    QString emH1 = QString::number(hh);

    pad = 0;

    minSize = hh;
    maxSize = hh*3;

    //this->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));


    //int iconSize = qMin( qMin( h , w) , this->maxSize) ;

    iconSize = QSize(maxSize, maxSize);

    //setMinimumSize(maxSize , maxSize);
    //setMinimumSize(maxSize , maxSize);
    //setFixedSize(maxSize , maxSize);
}


ButtonIconAutoResize::~ButtonIconAutoResize()
{

}

QSize ButtonIconAutoResize::sizeHint() const
{

    QSize sz = QToolButton::sizeHint( );

    QSize sz2 (maxSize , maxSize);

    //qDebug() << "ButtonIconAutoResize::sizeHint " << sz << sz2;

    return sz2;
}

void ButtonIconAutoResize::paintEvent( QPaintEvent *event )
{
    QStylePainter painter(this);

    QStyleOptionToolButton opt;

    this->initStyleOption(&opt);

    QRect rect = opt.rect;

    int h = rect.height();

    int w = rect.width();

    //qDebug() << "ButtonIconAutoResize rect " << rect;

    QIcon icn = icon();

    int min = qMin(rect.width() , rect.height());

    QIcon::Mode mode= QIcon::Normal;

    if( ! isEnabled())
        mode =QIcon::Disabled;
    else
        mode= QIcon::Normal;

    //qDebug() << " icn  " << objectName() << isEnabled();


    QPixmap pxm = icn.pixmap( min , min , mode );

    image = pxm.toImage();

    //alide

    painter.drawImage(opt.rect , image);
}
