#ifndef QP_SINGL_SLOT_SHOT_H
#define QP_SINGL_SLOT_SHOT_H

#include <QString>
#include <QStringList>
#include <QTimerEvent>

#include <QVector>
#include <QVariant>

#ifndef QT_NO_QOBJECT

#include <QtCore/qbasictimer.h> // conceptual inheritance
#include <QtCore/qobject.h>

//#include "private/qobject_p.h"

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE


class QpSingleShotTimer : public QObject
{
    Q_OBJECT
    int timerId;
public:
    ~QpSingleShotTimer();

    QpSingleShotTimer(
            int msec,
            QObject *slotOwner,
            const QString &slot_name,
            const QList<QVariant> &pars,
            QObject * parent);


    QObject *slotOwner;
    const QString slot_name;

    const QList<QVariant> pars;

Q_SIGNALS:

    void sig_retResult( bool resInvokeMethod, const QVariant& );

public slots:

    bool invokeMethod_slot_byName_withPars( QObject* obj,
                                            const QString & slot_name,
                                            const QList<QVariant> &map,
                                            QVariant &retVal);


protected:

    void timerEvent(QTimerEvent *);
};


QT_END_NAMESPACE

QT_END_HEADER

#endif // QT_NO_QOBJECT


#endif // QP_SINGL_SLOT_SHOT_H
