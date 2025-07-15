#ifndef EVT_PRETTY_LOOP_123_H
#define EVT_PRETTY_LOOP_123_H

#include <QEventLoop>
#include <QVariantMap>
#include <QPair>
#include <QTimer>


#include "qp/core/dll_qp_core_global.h"
class LIB_PREFIX_QP_CORE QpPrettyEvtLoop : public QEventLoop
{
    Q_OBJECT
public:

    typedef QPair < QObject*, QString > SGN;

    using QObject::d_ptr;

    explicit QpPrettyEvtLoop( const QList < QpPrettyEvtLoop::SGN > &lst, QObject *parent = 0);

    ~QpPrettyEvtLoop();

    int exec(ProcessEventsFlags flags = AllEvents);

    bool addTimer();

    bool restartTimer(int interval);
    int quit_result;

signals:
    void sig_evt();
    
public slots:
    void slot_quit();

private slots:
    //void testSlot();
private:

    QTimer *tmr;
    QList < SGN > llst;

    friend class QObjectPrivate;
};

#endif // EVT_LOOP_123_H
