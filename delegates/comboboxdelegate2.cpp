#include "comboboxdelegate2.h"

#include <QComboBox>
#include <QApplication>
#include <QDebug>

ComboBoxDelegate2::ComboBoxDelegate2( const QStringList &Lst,
                                      QWidget *parent) :
    QStyledItemDelegate(parent),
    lst(Lst),
    parent_(parent)

{

    int row=0;

    foreach ( QString str, lst )
    {
        QStringList ll = str.split(",");

        bool ok;

        int ii = ll.at(0).toInt( & ok );

        Q_ASSERT (ok==true);
        hashLst.insert( ii , row );
        row++;

    }


}


QWidget *ComboBoxDelegate2::createEditor(QWidget *parent,
                                         const QStyleOptionViewItem &option,
                                         const QModelIndex &index) const
{


    QComboBox *cmb = new QComboBox(parent);

    foreach ( QString str, lst )
    {
        QStringList ll = str.split(",");

        cmb->addItem( ll[1] , ll[0]);
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

    int ii = value.toInt(&ok);

    if(ok)
    {
        if ( hashLst.contains( ii ) )
        {
            int idx = hashLst[ ii ];

            if ( idx>=0 && idx <lst.count() )
            {
                return lst.at(idx);
            }
        }
    }

    return "";
}

void ComboBoxDelegate2::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    qDebug()<<"setEditorData"<<index;
}
