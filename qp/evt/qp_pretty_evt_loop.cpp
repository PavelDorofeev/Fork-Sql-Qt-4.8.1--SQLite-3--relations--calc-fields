#include "qp_pretty_evt_loop.h"
#include "qp/core/meta/meta.h"
#include <QDebug>
#include <QList>
#include <QMetaMethod>
//#include <QMutexLocker>



QpPrettyEvtLoop::QpPrettyEvtLoop( const QList < SGN > &lst ,
                    QObject *parent) :
    QEventLoop(parent),
    quit_result(0),
    tmr(0),
    llst(lst)
{

    //qDebug() <<  "Evt_Loop init:";
    for( int ii=0; ii<lst.count(); ii++)
    {
        SGN pp =lst.at( ii );

        //qDebug() <<  "cnct  pp.first"<< pp.first << " pp.second:" << pp.second;

        qp::meta::cnct( pp.first , pp.second , this , SLOT ( slot_quit()) , Qt::QueuedConnection);

        llst.append( pp );
    }
}

QpPrettyEvtLoop::~QpPrettyEvtLoop()
{
    if( tmr != 0 )
        delete tmr;
}

int QpPrettyEvtLoop::exec( ProcessEventsFlags flags )
{
    int result = QEventLoop::exec( flags );

    //qDebug() << "exec quit_result:"<<quit_result;

    return quit_result;
}

void QpPrettyEvtLoop::slot_quit()
{
    QObject * obj = qobject_cast<QObject*>( sender());

    QMetaMethod metaMethod = sender()->metaObject()->method( senderSignalIndex() );

    //QString sig_name = QString::number(senderSignalIndex()/2)+metaMethod.signature();
    QString sig_name = metaMethod.signature();


    bool found = false;

    for(int ii=0; ii < llst.count(); ii++)
    {
        if( llst.contains( SGN(obj , QString::number(ii)+sig_name )))
        {
            found = true;
            sig_name.prepend(QString::number(ii));
            //qDebug() << "found senderSignalIndex()"<< senderSignalIndex() << obj->objectName() << " sig_name" << sig_name;
            break;
        }
    }

    if( found )
    {
        quit_result = llst.indexOf( SGN (obj , sig_name) );
    }
    else
    {
        quit_result = -1;
        qDebug() << "ERROR: not found senderSignalIndex()"<< senderSignalIndex() << obj->objectName() << " sig_name" << sig_name;
    }


    QEventLoop::quit();
}


bool QpPrettyEvtLoop::restartTimer(int interval)
{
    //if( tmr->isActive())
    tmr->stop();

    tmr->setInterval( interval );

    tmr->start();

    return true;
}

bool QpPrettyEvtLoop::addTimer()
{
    tmr = new QTimer( this );

    //tmr->setInterval( interval );

    //qDebug() << "   pp.second: "<< SIGNAL(timeout());

    llst.append( SGN ( tmr , SIGNAL(timeout()) ));

    //tmr->start();

    return qp::meta::cnct( tmr , SIGNAL(timeout()) , this , SLOT ( slot_quit()));// , Qt::QueuedConnection );
}
