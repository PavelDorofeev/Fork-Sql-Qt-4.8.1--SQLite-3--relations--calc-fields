#include "comboboxdelegate2.h"

#include <QComboBox>
#include <QApplication>
#include <QDebug>
#include <QHash>

ComboBoxDelegate2::ComboBoxDelegate2( const QVariantList &lst,
                                      QWidget *parent) :
    QStyledItemDelegate(parent),
    //lst(Lst),
    parent_(parent)

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

        row++;

    }
}

ComboBoxDelegate2::ComboBoxDelegate2( const QHash<int,QString> &lst,
                                      QWidget *parent) :
    QStyledItemDelegate(parent),
    //lst(Lst),
    parent_(parent)

{
    int row=0;

    QHash<int,QString>::ConstIterator it = lst.constBegin();

    while (it != lst.constEnd())
    {
        int id = it.key();
        QString val = it.value();

        pair_lst.append( QPair < int , QString >( id , val ) );

        hashLst.insert( id , row );

        row++;

        it++;

    }
}


QWidget *ComboBoxDelegate2::createEditor(QWidget *parent,
                                         const QStyleOptionViewItem &option,
                                         const QModelIndex &index) const
{


    QComboBox *cmb = new QComboBox(parent);

    for( int ii=0; ii< pair_lst.count() ; ii++)
    {
        QPair < int , QString > pp = pair_lst.at( ii );
        //QStringList ll = str.split(",");

        cmb->addItem( pp.second , pp.first );
    }

    int width = 50;

    for(int ii=0; ii < cmb->count(); ii++)
    {
        if( width < QApplication::fontMetrics().width( cmb->itemText(ii)) )
            width = QApplication::fontMetrics().width( cmb->itemText(ii));
    }



    QPalette palette = option.palette;

    cmb->setPalette(palette);

    QStyleOptionViewItem opt = option;

    cmb->setSizeAdjustPolicy( QComboBox::AdjustToContents );

    cmb->setMinimumWidth( width);

    cmb->updateGeometry();


    return cmb;
}



void ComboBoxDelegate2::setModelData( QWidget *editor,
                                      QAbstractItemModel *model,
                                      const QModelIndex &index) const
{

    QComboBox *cmb = qobject_cast<QComboBox *>(editor);

    int idx=cmb->currentIndex();

    bool ok;

    QVariant val = cmb->itemData( idx , Qt::UserRole);

    bool setData = model->setData(index, val, Qt::EditRole);

    qDebug( ) << "setData " <<setData;

}


QString ComboBoxDelegate2::displayText( const QVariant &value,
                                        const QLocale &locale) const
{

    bool ok = false;

    int ii = value.toInt(&ok); // это значение в базе 1,11,12

    if(ok)
    {


        if ( hashLst.contains( ii ) )
        {
            int row = hashLst[ ii ];

            if ( row>=0 && row < pair_lst.count()) // ????????  lst.count() )
            {
                return pair_lst.at ( row ).second;
                //return lst.at (idx ).split(",").at(1);
            }
        }
    }

    return "";
}

void ComboBoxDelegate2::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    qDebug()<<"setEditorData"<<index;
}
