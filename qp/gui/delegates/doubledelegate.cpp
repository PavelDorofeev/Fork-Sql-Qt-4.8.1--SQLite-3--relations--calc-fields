#include "doubledelegate.h"
//#include <QAbstractItemView>
#include <QPainter>
#include <QDebug>
#include <QDoubleSpinBox>
#include "qp/gui/qp_doublespinbox.h"

#include "qp/qp.h"
#include "qp/core/meta/meta.h"


DoubleDelegate::DoubleDelegate( int Precision,
                                double Max,
                                double Min,
                                cb_test_double_value_func cb_Test_double_value  ,
                                QAbstractItemModel *Mdl,
                                QWidget *parent)
    :
      QStyledItemDelegate(parent)
    ,precision(Precision)
    ,min(Min)
    ,max(Max)
    ,cb_test_double_value(cb_Test_double_value)
    ,mdl(Mdl)
    ,idx(QModelIndex())
{


}

bool DoubleDelegate::cb_valueChanged( double dd )
{
    // -----------------------------------------------------
    // НЕ PАБОТАЕТ ПОЧЕМУ-ТО
    // -----------------------------------------------------

    qDebug() << "DoubleDelegate::cb_valueChanged" << dd;

    if( cb_test_double_value != 0 )
    {
        if( mdl && idx.isValid() )
        {
            if( ! cb_test_double_value( mdl , idx , dd ) )
                return false;
        }
    }

    return true;
}

void DoubleDelegate::slot_valueChanged(double dd)
{
    qDebug()<<"slot_valueChanged"<<dd;

    // -----------------------------------------------------
    // ТУТ ИДЕЯ В ЧЕМ - slot_valueChanged срабатывает и при интерактивном нажатии
    // на стрелки вверх/вниз QDoubleSpinBox
    // сам slot_valueChanged не запретит изменение, но откроет окно и ПPЕДУПPЕДИТ
    // ------------------------------------------------------

}

void DoubleDelegate::paint(QPainter *painter,
                           const QStyleOptionViewItem &option,
                           const QModelIndex &index) const
{


    QStyledItemDelegate::paint(painter, option, index);
}

void DoubleDelegate::setModelData(QWidget *editor,
                                  QAbstractItemModel *model,
                                  const QModelIndex &index) const
{

    qDebug() << "DoubleDelegate::setModelData" << index << model->data( index ,Qt::DisplayRole);

    //    if( mdl == 0 )
    //        mdl = model;

    //    if( ! idx.isValid() )
    //        idx = index;
    // -----------------------------------------------------------
    //      тут нужен контроль введенного значения
    //              вызов наружу
    // -----------------------------------------------------------

    if( cb_test_double_value != 0 )
    {
        QDoubleSpinBox *spnBx = qobject_cast<QDoubleSpinBox *>(editor);
        if( spnBx )
        {
            if( ! cb_test_double_value( model , index , spnBx->value() ) )
            {
                // ------------------------------------------------------
                // ТО ЧТО НАДО - НЕ ДАСТ ИЗМЕНИТЬ ЗНАЧЕНИЕ
                // В ВИДЖЕТЕ ВЕPНЕТ НАЗАД ПPЕДЫДУЩЕЕ ЗНАЧЕНИЕ
                // ------------------------------------------------------
                return;
            }
        }
    }

    QStyledItemDelegate::setModelData( editor, model, index );
}

void DoubleDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QpDoubleSpinBox * spnBx = qobject_cast<QpDoubleSpinBox *>(editor);

    if( spnBx )
        qDebug() << "DoubleDelegate::setEditorData" <<index << spnBx->value() ;

    if( ! idx.isValid() )
        idx = index;

    QStyledItemDelegate::setEditorData(editor, index );
}

QWidget *DoubleDelegate::createEditor( QWidget *parent,
                                       const QStyleOptionViewItem &option,
                                       const QModelIndex &index) const
{

    qDebug() << "createEditor";

    QpDoubleSpinBox * spnBx = new QpDoubleSpinBox( parent );//, this->cb_valueChanged);

    qp::meta::cnct( spnBx , SIGNAL(valueChanged(double)) ,this, SLOT( slot_valueChanged(double))) ;

    spnBx->setDecimals( precision );


    spnBx->setRange( min , max );

    qDebug()<< "maximum()" << spnBx->maximum();


    QPalette palette = option.palette;

    spnBx->setPalette(palette);

    return spnBx;
}


// -------------------------------------------------
// по умолчанию - maximum = 99.99
// -------------------------------------------------

//    int dd = DBL_MAX;
//    int ddd = DBL_DIG;
//#include <limits>

//    qDebug() << "DBL_MAX"<<dd;
//    qDebug() << "DBL_DIG"<<ddd;
//    qDebug() << "numeric_limits"<<std::numeric_limits<double>::max();
//    qDebug() << "sizeof(double)"<< sizeof(double);
