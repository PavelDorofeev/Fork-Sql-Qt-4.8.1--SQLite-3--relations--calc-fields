#ifndef QP_SINGL_SLOT_SHOT_H
#define QP_SINGL_SLOT_SHOT_H

#include <QString>
#include <QStringList>
#include <QTimerEvent>

#include <QVector>
#include <QVariant>

//#ifndef QT_NO_QOBJECT
#include <QtCore/qbasictimer.h> // conceptual inheritance
#include <QtCore/qobject.h>

//QT_BEGIN_HEADER

//QT_BEGIN_NAMESPACE

#include "qp/core/dll_qp_core_global.h"
class LIB_PREFIX_QP_CORE QpSingleShotTimer : public QObject
{
    Q_OBJECT
public:
    ~QpSingleShotTimer();

    QpSingleShotTimer(
            int msec,
            const QObject *slotOwner,
            const QString &slot_name,
            const QList<QVariant> &pars,
            QObject * parent);

    int timerId;

    const QObject *slotOwner;
    const QString slot_name;

    const QList<QVariant> pars;

Q_SIGNALS:

    void sig_retResult( bool resInvokeMethod, const QVariant& );

public slots:

    bool invokeMethod_slot_byName_withPars( const QObject* obj,
                                            const QString & slot_name,
                                            const QList<QVariant> &map,
                                            QVariant &retVal);


protected:

    void timerEvent(QTimerEvent *);
};


//QT_END_NAMESPACE

//QT_END_HEADER

//#endif // QT_NO_QOBJECT


#endif // QP_SINGL_SLOT_SHOT_H
