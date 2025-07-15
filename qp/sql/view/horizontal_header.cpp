#include "horizontal_header.h"

#include <QMessageBox>
#include <QDebug>
#include <QPainter>

Horizontal_Header::Horizontal_Header( QWidget *parent)
    :
      QHeaderView( Qt::Horizontal , parent)
{


//    if ( ! connect( this , SIGNAL(sectionPressed(int)),
//                    this, SLOT(slot_sectionPressed(int))))
//    {
//        QMessageBox::warning( this,
//                              "error",
//                              "connnect( this , SIGNAL(sectionPressed(int)),this, SLOT(slot_sectionPressed(int))");
//    }

    setHighlightSections( true );

    setMovable( true );

    setClickable ( true );


}

void Horizontal_Header::resizeSections( QHeaderView::ResizeMode mode )
{
    if( mode = QHeaderView::ResizeToContents)
    {

        const QAbstractItemModel *mdl = model();

        if( ! mdl )
            return ;


        int margin = style()->pixelMetric(QStyle::PM_HeaderMargin, 0, this);

        QFont fnt = font();
        fnt.setBold( true ); // this is important for section  selecting, cause this is adding section text width
        QFontMetrics mtr = QFontMetrics(fnt);


        for( int col=0; col <mdl->columnCount(); col++)
        {
            QString hdr = mdl->headerData(col , Qt::Horizontal ).toString();

            QRect rct = mtr.boundingRect( hdr );

            resizeSection( col , rct.width() + margin * 4 );

        }
        return;
    }

    QHeaderView::resizeSections( mode );
}

void Horizontal_Header::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    //qDebug() << "Horizontal_Header::paintSection logicalIndex " << logicalIndex;

    QHeaderView::paintSection(painter , rect , logicalIndex );
}


void Horizontal_Header::slot_sectionPressed(int section)
{
    qDebug() <<" slot_sectionPressed " <<section ;
}

Horizontal_Header::~Horizontal_Header()
{

}

void Horizontal_Header::mousePressEvent(QMouseEvent *event)
{
    //    if (event->button() == Qt::LeftButton)
    //    {
    //        qDebug() << "mousePressEvent event->pos() " <<event->pos();// << "  logicalIndexAt(event->pos())" << logicalIndexAt(event->pos());

    //        //emit sectionPressed( logicalIndexAt(event->pos()) );
    //        lastPressedSection = logicalIndexAt(event->pos());

    //        for( int ll = 0; ll < count(); ll++)
    //        {
    //            //                if ( ! isSectionHidden( logicNN) )
    //            //                    continue;

    //            //            qDebug() << "logicNN " << ll
    //            //                     << "  sectionPosition " << sectionPosition(ll)
    //            //                     << "   visualIndex " << visualIndex(ll)
    //            //                     << "  isSectionHidden " << isSectionHidden( ll );
    //        }

    //        //parent()

    //    }
    QHeaderView::mousePressEvent(event);
}

void Horizontal_Header::mouseMoveEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        qDebug() << "mouseMoveEvent";
    }

    QHeaderView::mouseMoveEvent(event);
}

//void Horizontal_Header::initialize_Sections()
//{
//    qDebug() << "initialize_Sections : " << count();
//    initializeSections(0 , count());
//}

void Horizontal_Header::mouseReleaseEvent(QMouseEvent *event)
{
    //    if (event->button() == Qt::LeftButton)
    //    {
    //        //qDebug() << "mouseReleaseEvent logicalIndexAt(event->pos())" << logicalIndexAt(event->pos());

    //        int toSection = logicalIndexAt(event->pos());

    //        if( toSection != lastPressedSection )
    //        {
    //            //qDebug() << "length " << length() << "  count() " << count();


    //            QList<int> lst;

    //            for( int ll = 0; ll < count(); ll++)
    //            {
    //                lst.append( visualIndex(ll) );
    //            }

    //            emit sig_needsReselect(lst);

    //        }
    //    }

    QHeaderView::mouseReleaseEvent(event);
}
