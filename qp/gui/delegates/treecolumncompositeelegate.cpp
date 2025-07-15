#include "treecolumncompositedelegate.h"

#include <QComboBox>
#include <QApplication>
#include <QDebug>
#include <QHash>

TreeColumnCompositeDelegate::TreeColumnCompositeDelegate( const QVariantList &lst,
                                      QWidget *parent) :
    QStyledItemDelegate(parent),
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

TreeColumnCompositeDelegate::TreeColumnCompositeDelegate( const QHash<int,QString> &lst,
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


QWidget *TreeColumnCompositeDelegate::createEditor(QWidget *parent,
                                         const QStyleOptionViewItem &option,
                                         const QModelIndex &index) const
{
    qDebug()<<"createEditor index"<<index;

    QComboBox *cmb = new QComboBox(parent);

    for( int ii=0; ii< pair_lst.count() ; ii++)
    {
        QPair < int , QString > pp = pair_lst.at( ii );
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



void TreeColumnCompositeDelegate::setModelData( QWidget *editor,
                                      QAbstractItemModel *model,
                                      const QModelIndex &index) const
{
    qDebug()<<"setModelData index"<<index<< " editor"<<editor->objectName() << " model"<<model->objectName();

    QComboBox *cmb = qobject_cast<QComboBox *>(editor);

    int idx=cmb->currentIndex();

    bool ok;

    QVariant val = cmb->itemData( idx , Qt::UserRole);

    bool setData = model->setData(index, val, Qt::EditRole);

    qDebug( ) << "setData " <<setData;

}


QString TreeColumnCompositeDelegate::displayText( const QVariant &value,
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

void TreeColumnCompositeDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    qDebug()<<"setEditorData"<<index;
}
