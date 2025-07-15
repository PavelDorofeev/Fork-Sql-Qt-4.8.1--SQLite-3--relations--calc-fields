#include "qp_combobox.h"

#include <QDebug>

#include "equipment/a_subdirs/abstract_kkt/qp_treeitem_2.h"

QpComboBox::QpComboBox(QWidget *parent) :
    QComboBox(parent),
    treeItem(0)
{

}
void QpComboBox::mousePressEvent(QMouseEvent * e)
{
    QComboBox::mousePressEvent( e );
}

bool QpComboBox::commitData( const QVariant &newVal )
{
    emit sig_commitData( newVal );

    return true;
}

void QpComboBox::paintEvent( QPaintEvent *e )
{
    //setBackgroundRole( QPalette::AlternateBase );//QPalette::AlternateBase);//  ,);
    //setPalette( QColor(Qt::magenta));

    //QAbstractItemModel *mdl = model();

    QComboBox::paintEvent( e );
}


void QpComboBox::wheelEvent(QWheelEvent *event)
{

    // отключаем
}

void QpComboBox::slot_dataChanged_2( const QVariant & newVal)
{
    /*
      Нам нужен этот слот , потому что Комбобокс  сам не обновится

    */

    int newPos = findData( newVal );

    if( newPos >=0 && currentIndex() != newPos )
    {
        /*
          в чем тут прикол?
          нам не надо вызывать сигнал currentIndexChanged

        */

        bool bb = blockSignals( true );

        //Q_ASSERT ( bb );

        // -------------------------------------------

        setCurrentIndex( newPos );

        // -------------------------------------------


        bb = blockSignals( false );

        //Q_ASSERT ( bb );
    }

}
