#include "meta.h"
#include <QDebug>
#include <QCoreApplication>
#include <QSettings>
//#include <QMessageBox>
//#include <QLineEdit>


namespace qp {



namespace meta {


// переменные не надо в h файле объявлять

static const QString err1 = QString::fromUtf8("не инициализированы QApplication::organizationName() или QApplication::applicationName(), сохранение параметров не будет работать");


bool saveToReestr(const QString &key , const QVariant& val)
{
    // используй префикс xxx/value  для помещения в каталог


    if( QCoreApplication::organizationName().isEmpty() || QCoreApplication::applicationName().isEmpty())
    {
        qCritical() << qp::meta::err1;
        Q_ASSERT_X(1==64563654 , qp::meta::err1.toLocal8Bit() , qp::meta::err1.toLocal8Bit());
//        QMessageBox::warning( 0 ,
//                              QString::fromUtf8("внимание"),
//                              qp::meta::err1
//                              );
        return false;
    }

    QSettings sett( QCoreApplication::organizationName() , QCoreApplication::applicationName() );
    sett.setValue( key , val );

    return true;

}

QVariant initFromReestr( const QString &key )
{
    if( QCoreApplication::organizationName().isEmpty() || QCoreApplication::applicationName().isEmpty() )
    {
        qCritical() << qp::meta::err1;
        Q_ASSERT_X(1==64563654 , qp::meta::err1.toLocal8Bit() , qp::meta::err1.toLocal8Bit());
//        QMessageBox::warning( 0 ,
//                              QString::fromUtf8("внимание"),
//                              qp::meta::err1
//                              );
        return QVariant();
    }

//    if( qobject_cast<QLineEdit*>(obj) )
//    {
//        qp::meta::cnct ( obj , SIGNAL( editingFinished()),
//                         this, SLOT( slot_ledt_FNdocNum_editingFinished()));
//    }

    QSettings sett( QCoreApplication::organizationName() ,QCoreApplication::applicationName() );
    return sett.value( key );

}

bool cnct( const QObject * snd, const QString &sgn,
           const QObject * rcv, const QString &slt,
           Qt::ConnectionType type)
{

    if( ! QObject::connect ( snd , sgn.toLocal8Bit() , rcv , slt.toLocal8Bit(), type ) )
    {
        qCritical() << "!!!! Error connect(..) signal : " << sgn << " / slot : " << slt;

        Q_ASSERT_X(1==64563654 , qp::meta::err1.toLocal8Bit() , qp::meta::err1.toLocal8Bit());
//        QMessageBox::critical(0 ,
//                              "Error signal/slot connect",
//                              QString("Error connect(..):\n%1\n %2\n %3\n %4 ")
//                              .arg (snd->objectName())
//                              .arg(sgn)
//                              .arg(rcv->objectName())
//                              .arg(slt)
//                              );

        return false;
    }

    return true;
}

bool dis_cnct( const QObject * snd, const QString &sgn,
               const QObject * rcv, const QString &slt)
{

    if( ! QObject::disconnect( snd , sgn.toLocal8Bit() , rcv , slt.toLocal8Bit() ) )
    {
        qCritical() << "!!!! Error connect(..) signal : " << sgn << " / slot : " << slt;
        Q_ASSERT(1==64563654);

//        QMessageBox::critical(0 ,
//                              "Error signal/slot disconnect",
//                              QString("Error disconnect(..):\n%1\n %2\n %3\n %4 ")
//                              .arg (snd->objectName())
//                              .arg(sgn)
//                              .arg(rcv->objectName())
//                              .arg(slt)
//                              );

        return false;
    }

    return true;
}



}

}
