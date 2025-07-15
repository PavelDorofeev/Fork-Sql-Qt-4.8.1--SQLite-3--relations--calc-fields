#include "treecolumncompositedelegate.h"

#include <QComboBox>
#include <QApplication>
#include <QDebug>
#include <QHash>
#include <QMap>
#include <QComboBox>


TreeColumnCompositeDelegate::TreeColumnCompositeDelegate( const QMap<int, Tag_Value> &map,
                                                          QWidget *parent) :
    QStyledItemDelegate(parent),
    parent_(parent)

{

}


QWidget *TreeColumnCompositeDelegate::createEditor( QWidget *parent,
                                                    const QStyleOptionViewItem &option,
                                                    const QModelIndex &index) const
{
    qDebug()<<"createEditor index"<<index;

    int row = index.row();

    if( ! wgt.contains( row ))
        return 0;

    QWidget *currWgt = wgt.value( row );


    qDebug() << "parent->rect()" << parent->rect();

    QPalette palette = option.palette;

    currWgt->setPalette(palette);

    QStyleOptionViewItem opt = option;

    //currWgt->setSizeAdjustPolicy( QComboBox::AdjustToContents );

    //cmb->setMinimumWidth( width);

    currWgt->updateGeometry();

    return currWgt;
}



void TreeColumnCompositeDelegate::setModelData( QWidget *editor,
                                                QAbstractItemModel *model,
                                                const QModelIndex &index) const
{
    //mdl = model;

    qDebug()<<"setModelData index"<<index<< " editor"<<editor->objectName() << " model"<<model->objectName();


}


QString TreeColumnCompositeDelegate::displayText( const QVariant &value,
                                                  const QLocale &locale) const
{

    bool ok = false;



//    if( ! wgt.contains( row ))
//        return 0;

    //QWidget *currWgt = wgt.value( row );


    /*int ii = value.toInt(&ok); // это значение в базе 1,11,12

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
    }*/

    return value.toString();
}

void TreeColumnCompositeDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    qDebug()<<"setEditorData"<<index;
}
