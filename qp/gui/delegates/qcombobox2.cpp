#include "qcombobox2.h"
#include <QDebug>

QComboBox2::QComboBox2( const QVariantList &Lst,
                        QWidget *parent)
    :
    QComboBox(parent),
      lst ( Lst )
{
    int row=0;

    foreach ( QVariant var, lst )
    {
        if( ! var.canConvert( QVariant::String ))
            continue;

        QString str = var.toString();

        bool ok;

        int id = str.split(",").value(0).toInt( &ok );

        Q_ASSERT (ok==true);

        if( ! ok )
            continue;

        QString strVal = str.split(",").value(1);

        pair_lst.append( QPair < int , QString >( id , strVal) );

        hashLst.insert( id , row );
        hashLst2.insert( row , id );

        addItem( strVal , id );

        row++;

    }
}

int QComboBox2::currentIndex()
{
    int row = QComboBox::currentIndex();

    if( ! hashLst2.contains( row ) )
        return -1;

    return hashLst2.value( row );
}

void QComboBox2::setCurrentIndex( int idx_db )
{
    if( hashLst.contains( idx_db ) )
    {
        int row = hashLst[ idx_db ];

        QComboBox::setCurrentIndex( row );
        //qDebug() << "QComboBox2::setCurrentIndex" << currentIndex();
    }

}
