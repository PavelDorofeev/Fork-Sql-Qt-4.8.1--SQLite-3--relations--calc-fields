#include "qp_doublespinbox.h"
#include <QDebug>

QpDoubleSpinBox::QpDoubleSpinBox(
        QWidget *parent,
        cb_test_double_value_func2 cb_Test_double_value_func2
        )
    :
    QDoubleSpinBox(parent),
    treeItem(0),
    cb_test_double_value2( cb_Test_double_value_func2 )
{

}

double QpDoubleSpinBox::valueFromText(const QString &text) const
{
    //qDebug()<<"QpDoubleSpinBox::valueFromText" << text;



    return QDoubleSpinBox::valueFromText( text);
}

void QpDoubleSpinBox::mousePressEvent(QMouseEvent *evt)
{
    //qDebug() << "QpDoubleSpinBox::mousePressEvent";

    QDoubleSpinBox::mousePressEvent( evt);

}
void QpDoubleSpinBox::changeEvent(QEvent *evt)
{
    //qDebug() << "QpDoubleSpinBox::changeEvent";

    QDoubleSpinBox::changeEvent( evt);
}

QValidator::State QpDoubleSpinBox::validate(QString &input, int &pos) const
{

    //qDebug() <<"QpDoubleSpinBox::validate"<<input << pos;
    //bool ok;

//    if( cb_test_double_value2 != 0 )
//    {
//        double dd = input.toDouble( &ok );

//        Q_ASSERT(ok);


        //if( ! cb_test_double_value2( dd ) )
        //{
            //qDebug() << "QValidator::Invalid";  // PАБОТАЕТ

            //return QValidator::Invalid;
        //}
   // }

    return QDoubleSpinBox::validate( input, pos );

}
void QpDoubleSpinBox::setValue(double val)
{

    //qDebug() <<"QpDoubleSpinBox::setValue"<<val;

    // контроллируем ввод значения

    if( cb_test_double_value2 != 0 )

        if( ! cb_test_double_value2( val ) )

            return;

    QDoubleSpinBox::setValue( val);
}

void QpDoubleSpinBox::wheelEvent(QWheelEvent *event)
{
    // отключаем
}
