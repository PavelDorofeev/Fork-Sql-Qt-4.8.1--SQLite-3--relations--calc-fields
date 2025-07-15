#include "qpmulticomboboxitemsdelegate.h"
#include "qp/gui/qp_multicombobox.h"

#include <QMessageBox>
#include "qp/gui/qp_gui.h"
#include "qp/core/qp_core.h"
#include "QDebug"
#include "QString"

QpMultiComboBoxItemsDelegate::QpMultiComboBoxItemsDelegate(QWidget *parent)
    :
      QStyledItemDelegate( parent )
    ,checkedBitsLimit(-1)
    ,prnt(parent)
{
    QpMultiComboBox * mltCmb = qobject_cast<QpMultiComboBox *>(parent);

    if ( mltCmb )
    {
        qp::meta::cnct( this , SIGNAL(sig_something_changed()) , mltCmb, SLOT (slot_something_changed()));

    }
}

void QpMultiComboBoxItemsDelegate::paint(QPainter *painter,
                                         const QStyleOptionViewItem &option,
                                         const    QModelIndex &index) const
{
    // Custom painting code here
    // For example, you could draw the items with a different background color or font
    QStyledItemDelegate::paint(painter, option, index);
}


bool QpMultiComboBoxItemsDelegate::toggleChecked( QAbstractItemModel *mdl, const QModelIndex &idx)
{
    Qt::ItemFlags flgs = mdl->flags( idx);

    qDebug() << "flgs : " << flgs;

    if( ! ( flgs & Qt::ItemIsEditable) )
        return true;

    if( ! ( flgs & Qt::ItemIsEnabled) )
        return true;

    bool checked = mdl->data( idx , Qt::CheckStateRole).toBool();


    if( checked )
    {
        bool rs = mdl->setData( idx , Qt::Unchecked, Qt::CheckStateRole);
        emit sig_something_changed();
        return rs;
    }
    else
    {

        int nmbr = checkedBitsNumber( mdl );

        if( checkedBitsLimit == -1 || nmbr < checkedBitsLimit  )
        {
            bool rs = mdl->setData( idx , Qt::Checked, Qt::CheckStateRole);
            emit sig_something_changed();
            return rs;
        }
        else
        {
            if( nmbr == 1 && checkedBitsLimit == 1)
            {
                setAllCheckedToNone( mdl );

                bool rs = mdl->setData( idx , Qt::Checked, Qt::CheckStateRole);
                emit sig_something_changed();
                return rs;

            }

            QMessageBox::warning( prnt ,
                       "Превышен лимит выбора",
                       QString("Pазрешено выбирать только %1 значения из списка")
                       .arg( checkedBitsLimit)
                       );

            return false;
        }
    }
}

int QpMultiComboBoxItemsDelegate::checkedBitsNumber( QAbstractItemModel *model) const
{
    int cnt =0 ;
    for( int row=0; row < model->rowCount(); row++)
    {
        QModelIndex index = model->index( row, 0);

        if ( model->data( index , Qt::CheckStateRole).toBool() )
            cnt++;
    }
    return cnt;
}

bool QpMultiComboBoxItemsDelegate::editorEvent( QEvent *event,
                                                QAbstractItemModel *model,
                                                const QStyleOptionViewItem &option,
                                                const QModelIndex &index)
{

    if( event->type() != QEvent::MouseMove )
        qDebug() << "Delegate editorEvent " << qp::dbg_core::toStr_Event_Type( event->type())
                 << model << option << " index" << index;

    if( event->type() == QEvent::MouseButtonPress )
    {
        return toggleChecked( model , index );
    }
    else if( event->type() == QEvent::KeyPress )
    {
        QKeyEvent *ee = (QKeyEvent*)(event);

        //qDebug() << "ee" << ee->key() << ee->text();

        return toggleChecked( model , index );
    }
    else
    {

        return QStyledItemDelegate::editorEvent( event , model , option , index );
    }
}

void  QpMultiComboBoxItemsDelegate::setAllCheckedToNone( QAbstractItemModel *mdl)
{

    for (int i = 0; i < mdl->rowCount(); ++i)
    {
        QModelIndex index = mdl->index( i , 0 );

        bool bb = mdl->setData( index , Qt::Unchecked, Qt::CheckStateRole);

        Q_ASSERT( bb ==true);
    }
}


//void QpMultiComboBoxItemsDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
//{
//    qDebug() << "setEditorData index" << index;

//    QStyledItemDelegate::setEditorData( editor , index );
//}

//bool QpMultiComboBoxItemsDelegate::eventFilter( QObject *object, QEvent *event)
//{
//    qDebug() << "Delegate eventFilter " << qp::dbg::toStr_Event_Type( event->type())
//             << object;

//    if(event->type() == QEvent::MouseButtonPress)
//    {
//        qDebug() << "Delegate QEvent::MouseButtonRelease";
//        QpMultiComboBox *cmb = qobject_cast<QpMultiComboBox*>(object);

//        if ( ! cmb )
//            qDebug()<<"sdfdsfdsfd";
//        return true;
//    }
//    else
//    {
//        return QStyledItemDelegate::eventFilter( object , event );
//    }
//}
