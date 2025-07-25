#include "qpsingleshottimer.h"

#include "private/qobject_p.h"
#include "qabstracteventdispatcher.h"
#include <QDebug>

//QT_BEGIN_NAMESPACE

QpSingleShotTimer::QpSingleShotTimer( int msec,
                                      const QObject *SlotOwner,
                                      const QString &Slot_name,
                                      const QList<QVariant> &Pars ,
                                      QObject * parent)

    :
      QObject( QAbstractEventDispatcher::instance() ), ////????
      slot_name(Slot_name),
      slotOwner(SlotOwner),
      pars(Pars)
{

    timerId = startTimer(msec);

    //qDebug() << "SlotOwner" << SlotOwner->objectName();
}

QpSingleShotTimer::~QpSingleShotTimer()
{
    if (timerId > 0)
        killTimer(timerId);
}

bool QpSingleShotTimer::invokeMethod_slot_byName_withPars( const QObject* slotOwner,
                                                           const QString & slot_name,
                                                           const QList<QVariant> &map,
                                                           QVariant &retVal)
{
    QList<QGenericArgument> lst;

    //qDebug() << "invokeMethod_slot_byNam_withPars  slotOwner " << slotOwner->objectName() << " map:" << map;

    QList<QVariant>::ConstIterator it = map.constBegin();


    while (it != map.constEnd())
    {
        const QVariant& var = *it;

        lst.append( QGenericArgument( var.typeName() , var.constData() ) );

        ++it;
    }

    //QVariant retval;
    QGenericReturnArgument  retArg;
    retArg = QGenericReturnArgument("QVariant", &retVal);

    QObject* slotOwner_ = const_cast<QObject*>(slotOwner);

    //qDebug() << "QpSingleShotTimer::invokeMethod_slot_byName_withPars slotOwner_"<<slotOwner_->objectName() <<"slot_name"<<slot_name;
    //qDebug() << slot_name.toLocal8Bit().constData()<< "lst.count()"<<lst.count();

    if( ! slotOwner_)
    {
        qWarning() << "error: const_cast<QObject*>(slotOwner)" << slotOwner->objectName();
        return false;
    }


//    if ( ! QMetaType::isRegistered(QMetaType::type("ConnectOfd")))
//    {
//        qDebug()<<" ! QMetaType::isRegistered(QMetaType::type(\"ConnectOfd\")";
//    }

//    qDebug()<< "QMetaType::type(\"ConnectOfd\")"<<QMetaType::type("ConnectOfd");

//    qDebug()<< "slot_name.toLatin1().constData()"<< slot_name.toLatin1().constData();
//    qDebug()<< "slot_name.toLocal8Bit().constData()"<< slot_name.toLocal8Bit().constData();
//    qDebug()<< "slot_name.toAscii().constData()"<<slot_name.toAscii().constData();

    bool resInvokeMethod = QMetaObject::invokeMethod( slotOwner_ ,
                                                      slot_name.toLatin1().constData(), // имя слота
                                                      Qt::DirectConnection,//Qt::QueuedConnection,
                                                      retArg,
                                                      //                                          Q_ARG(double, 1.23),
                                                      //                                          Q_ARG(QString, "asdasds"),
                                                      //                                          Q_ARG(QString, "")
                                                      lst.count()>0 ? lst[0] : QGenericArgument(),
                                                      lst.count()>1 ? lst[1] : QGenericArgument(),
                                                      lst.count()>2 ? lst[2] : QGenericArgument(),
                                                      lst.count()>3 ? lst[3] : QGenericArgument(),
                                                      lst.count()>4 ? lst[4] : QGenericArgument(),
                                                      lst.count()>5 ? lst[5] : QGenericArgument(),
                                                      lst.count()>6 ? lst[6] : QGenericArgument(),
                                                      lst.count()>7 ? lst[7] : QGenericArgument(),
                                                      lst.count()>8 ? lst[8] : QGenericArgument(),
                                                      lst.count()>9 ? lst[9] : QGenericArgument()
                                                                      );

    //qDebug()<<"QMetaObject::invokeMethod = "<<resInvokeMethod ;

    //qDebug() <<"retVal"<<retVal;

    return resInvokeMethod;

}

void QpSingleShotTimer::timerEvent(QTimerEvent *)
{

    if (timerId > 0)
        killTimer(timerId);

    timerId = -1;

    QVariant retVal;

    bool resInvokeMethod = invokeMethod_slot_byName_withPars( slotOwner , slot_name , pars , retVal);

    emit sig_retResult( resInvokeMethod, retVal );

    // we would like to use delete later here, but it feels like a
    // waste to post a new event to handle this event, so we just unset the flag
    // and explicitly delete...

    qDeleteInEventHandler(this);
}

//QT_END_NAMESPACE
