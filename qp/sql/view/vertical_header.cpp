#include "vertical_header.h"


Vertical_Header::Vertical_Header(QWidget *parent) :
    QHeaderView( Qt::Vertical,  parent)
{

    int margin = style()->pixelMetric(QStyle::PM_HeaderMargin, 0, this);

    //setDefaultSectionSize( appDef::em3.toInt() + margin *2 );

    //setResizeMode( ResizeToContents );

    setVisible( true );

}


//void Vertical_Header::resizeSections( QHeaderView::ResizeMode mode )
//{
//    if( mode = QHeaderView::ResizeToContents)
//    {

//        const QAbstractItemModel *mdl = model();

//        if( ! mdl )
//            return ;


//        int margin = style()->pixelMetric(QStyle::PM_HeaderMargin, 0, this);

//        QFontMetrics mtr = QFontMetrics(font());


//        for( int row=0; row < mdl->rowCount(); row++)
//        {
//            resizeSection( row , appDef::em3.toInt() + margin *2 );
//        }
//        return;
//    }

//    QHeaderView::resizeSections( mode );
//}

//int Vertical_Header::sectionSizeHint( int logicalIndex )
//{
//    int margin = style()->pixelMetric(QStyle::PM_HeaderMargin, 0, this);

//    int std = QHeaderView::sectionSizeHint( logicalIndex );

//    return appDef::em3.toInt() + margin *2;
//}

//int Vertical_Header::sectionSize(int logicalIndex) const
//{
//    int margin = style()->pixelMetric(QStyle::PM_HeaderMargin, 0, this);

//    int std = QHeaderView::sectionSize( logicalIndex );

//    return appDef::em3.toInt() + margin *2;
//}
