#include "combobox_delegate.h"
#include <QComboBox>
#include <QDebug>
#include "some_tests.h"
#include <QApplication>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QPalette>


ComboBoxDelegate::ComboBoxDelegate(PblSqlRelationalTableModel *mdl,
                                   int column,
                                   QStringList &lst_,
                                   QWidget *parent)
    : QStyledItemDelegate(parent)

{
    column_=column;
    lst=lst_;
    mdl_=mdl;

}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const
{
    //qDebug() << QString("ComboBoxDelegate::createEditor [%1x%2] parent objName %3 option  ").arg(index.row()).arg(index.column()).arg(parent->objectName()) << option;


    QComboBox *cmb = new QComboBox(parent);
    cmb->insertItems(0,lst);

    _CONNECT_(cmb,  SIGNAL(activated(int)), this, SLOT(slot_commitAndCloseEditor(int)));

    QPalette palette = option.palette; //editor->palette();

    cmb->setPalette(palette);

    return cmb;
}

void ComboBoxDelegate::slot_commitAndCloseEditor(int pos)
{
    QComboBox *editor = qobject_cast<QComboBox *>(sender());
    //emit commitData(editor);
    //emit closeEditor(editor);
}

void ComboBoxDelegate::setModelData(QWidget *editor,
                                    QAbstractItemModel *model,
                                    const QModelIndex &index) const
{

    QComboBox *edit = qobject_cast<QComboBox *>(editor);

    int newValue=edit->currentIndex();

    bool res = model->setData(index, newValue, Qt::EditRole);

}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor,
                                            const QStyleOptionViewItem &option,
                                            const QModelIndex &index) const
{
    //qDebug() << QString("ComboBoxDelegate::updateEditorGeometry [%1x%2] option ").arg(index.row()).arg(index.column()) << "  option : " << option;

    editor->setGeometry(option.rect);
}



QString ComboBoxDelegate::displayText(const QVariant &value,
                                      const QLocale &locale) const
{
    // это по каждому элементу выпадающего списка

    //qDebug() << QString("ComboBoxDelegate::displayText ")  << objectName() << "  value : " << value.toString();

    QString str=value.toString();
    return str;
}


void ComboBoxDelegate::paint(QPainter *painter,
                             const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{

    if(index.column()== column_)
    {
        int col=index.column();
        int row=index.row();

        //option.palette.setColor(QPalette::Normal, QPalette::Background, Qt::red);

        QStyleOptionComboBox style;

        if (option.state & QStyle::State_Selected)
        {
            painter->setPen(QPen(option.palette.color(QPalette::HighlightedText))); // Цвет пера
            painter->fillRect(option.rect, option.palette.highlight());
        }
        else if (option.state & (QStyle::State_Enabled ))
        {
            painter->setPen(QPen(option.palette.color(QPalette::Text))); // Цвет пера
            painter->fillRect(option.rect, option.palette.base());

        }

        // последовательность drawComplexControl и drawControl ИМЕЕТ ЗНАЧЕНИЕ !!!

        painter->save();

        QString text="";

        if(mdl_->index(row,col).isValid())
        {
            int ii=mdl_->data(mdl_->index(row,col)).toInt();

            if( ii >=0)
                text = lst.at(ii);
            else
                text="";

        }

        painter->drawText(option.rect, Qt::AlignLeft | Qt::AlignVCenter, text);

        painter->restore();

    }
    else
        QStyledItemDelegate::paint(painter , option , index);

}


void ComboBoxDelegate::slot_currentIndexChanged(int pos)
{
    QComboBox *cmb=qobject_cast<QComboBox*>(sender());

    qDebug() << "ComboBoxDelegate::slot_currentIndexChanged : " << cmb->currentIndex();

    //emit commitData(cmb);
}
