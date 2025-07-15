#include "qp_multicombobox.h"

#include <QStylePainter>
#include <QMouseEvent>
#include <QDebug>
#include "qp/gui/qpmulticomboboxitemsdelegate.h"
//#include "abstract_kkt/qp_treeitem_2.h"


QpMultiComboBox::QpMultiComboBox(QWidget *parent) :
    QComboBox(parent)
  ,selectable(true)
{
    //setStyleSheet("QComboBox { combobox-popup: 1px }");
    dlgt = new QpMultiComboBoxItemsDelegate( this );

    setItemDelegate( dlgt );

}


QpMultiComboBox::~QpMultiComboBox()
{
}

void QpMultiComboBox::set_MaxBitsNumberSelecting(int maxNum)
{
    dlgt->checkedBitsLimit = maxNum;
}

void QpMultiComboBox::wheelEvent(QWheelEvent *event)
{

}
//void QpMultiComboBox::mousePressEvent( QMouseEvent *evt )
//{
//    // сработка при выпадании списка  ( клик по стрелке вниз)
////    if( ! selectable )
////        return;

//    qDebug() << "QpMultiComboBox::mousePressEvent:" <<evt->pos();
//    QComboBox::mousePressEvent(evt);
//}

//void QpMultiComboBox::mouseReleaseEvent( QMouseEvent *evt )
//{
//    // сработка при сворачивании выпавшего списка ( клик по стрелке вниз)

////    if( ! selectable )
////        return;

//    qDebug() << "QpMultiComboBox::mouseReleaseEvent:" <<evt->pos();

//    QComboBox::mouseReleaseEvent(evt);

//}

//void QpMultiComboBox::keyPressEvent(QKeyEvent *evt)
//{
//    if( ! selectable )
//        return;


//    qDebug() << "QpMultiComboBox::keyPressEvent text:" <<evt->text();

//    QComboBox::keyPressEvent(evt);

//}

//void QpMultiComboBox::inputMethodEvent(QInputMethodEvent *evt)
//{

//    qDebug() << "QpMultiComboBox::inputMethodEvent :"
//                // <<evt->attributes()
//             << evt->preeditString()
//             << evt->commitString()
//             << "currentIndex" << currentIndex()
//                ;


//    QComboBox::inputMethodEvent(evt);

//}



void QpMultiComboBox::slot_something_changed()
{
    //repaint();

    emit sig_something_changed();
}

bool QpMultiComboBox::fillContent( const QMap<int,QString> & ll , const uint &currVal)
{
    QMap<int,QString>::ConstIterator  it2 = ll.constBegin();

    while( it2 != ll.constEnd() )
    {
        int val = 1 << it2.key(); // номер бита

        addItem( it2.value() , val );

        it2++;
    }

    markBits( currVal );


    return true;
}

bool QpMultiComboBox::markBits( const uint &currVal ) const
{

    set_checkedBitsToNone();

    uint vv = currVal;

    for(int ii=0; ii< 32; ii++) // по битам идем
    {
        if( vv & 0x0001)
        {
            int tt = 1 << ii;
            setCheckedItem( tt );
        }

        vv = vv >> 1;
    }


    return true;
}


void QpMultiComboBox::setCheckedItem(const int& itemVl) const
{
    int foundIndex = findData( itemVl );

    Q_ASSERT(foundIndex>=0);

    QStandardItemModel *standartModel = qobject_cast<QStandardItemModel*>(model());


    if ( foundIndex >=0 )
    {
        //if( maxBitsNumberSelecting )
        standartModel->item( foundIndex )->setData( Qt::Checked, Qt::CheckStateRole );
        //repaint();
        //emit sig_something_changed();
    }
}

uint  QpMultiComboBox::getCopmlexValue()
{

    QStandardItemModel *mdl = qobject_cast<QStandardItemModel*>(model());

    Q_ASSERT ( mdl !=0);

    uint retVl=0;

    for (int ii = 0; ii < mdl->rowCount(); ++ii)
    {
        QModelIndex itmIdx = mdl->index( ii , 0 );


        if( mdl->data( itmIdx , Qt::CheckStateRole).toBool() )
        {
            QVariant val = itemData( ii );

            bool ok;
            int bitVal = val.toUInt( &ok ); // это значение бита

            Q_ASSERT(ok==true);

            //int iVl = 1 << bitVal;

            retVl += bitVal;
        }
    }

    return retVl;
}

void  QpMultiComboBox::set_checkedBitsToNone() const
{
    QStandardItemModel *mdl = qobject_cast<QStandardItemModel*>(model());

    for (int i = 0; i < mdl->rowCount(); ++i)
    {
        QModelIndex index = mdl->index( i , 0 );

        bool bb = mdl->setData( index , Qt::Unchecked, Qt::CheckStateRole);

        Q_ASSERT( bb ==true);
    }
    //emit sig_something_changed();
    //repaint();

}


void QpMultiComboBox::paintEvent(QPaintEvent *event)
{

    QStandardItemModel *mdl = qobject_cast<QStandardItemModel*>(model());

    QString str;

    for (int i = 0; i < mdl->rowCount(); ++i)
    {
        QModelIndex index = mdl->index( i , 0 );

        bool checked = mdl->data( index , Qt::CheckStateRole).toBool();


        if( checked )
        {
            if(! str.isEmpty())
                str.append(",");

            str.append( itemText( i ));
        }

    }

    QStyleOptionComboBox opt;
    initStyleOption(&opt);

    QStylePainter p(this);
    p.drawComplexControl(QStyle::CC_ComboBox, opt);

    QRect textRect = style()->subControlRect(QStyle::CC_ComboBox, &opt, QStyle::SC_ComboBoxEditField, this);
    opt.currentText = p.fontMetrics().elidedText( str , Qt::ElideRight, textRect.width());
    p.drawControl(QStyle::CE_ComboBoxLabel, opt);

    //QComboBox::paintEvent( event);

}

void QpMultiComboBox::resizeEvent(QResizeEvent *event)
{
}


void QpMultiComboBox::set_selectable( bool bb)
{
    selectable = bb;

    //dlgt->set

    QStandardItemModel * mdl = qobject_cast<QStandardItemModel *>(model());

    if( ! mdl )
        return;

    for( int row=0; row < mdl->rowCount(); row++ )
    {
        QStandardItem *item = mdl->item( row );

//        if( ! item )
//            return;

        Qt::ItemFlags flgs = item->flags();

        if( selectable )
        {
            flgs |= Qt::ItemIsEnabled;
            flgs |= Qt::ItemIsSelectable;
            flgs |= Qt::ItemIsEditable;
            flgs |= Qt::ItemIsUserCheckable;
            flgs |= Qt::ItemIsDragEnabled;
            flgs |= Qt::ItemIsDropEnabled;
        }
        else
        {
            flgs &= ~Qt::ItemIsEnabled;
            flgs &= ~Qt::ItemIsSelectable;
            flgs &= ~Qt::ItemIsEditable;
            flgs &= ~Qt::ItemIsUserCheckable;
            flgs &= ~Qt::ItemIsDragEnabled;
            flgs &= ~Qt::ItemIsDropEnabled;
        }

        item->setFlags ( flgs ) ;

        //qDebug() << "set_selectable flgs:" << flgs;
    }

    return;

}

QDebug operator<<(QDebug d,const QpMultiComboBox &cmb) {

    d << "\n------------------ QpMultiComboBox -------------------";

    for( int ii=0; ii < cmb.count(); ii++)
    {
        d << "\n\t "<< ii << " : " << cmb.itemData( ii )<< cmb.itemText( ii );
    }

    d << "\n-------------------------------------------------";

    return d;
}
