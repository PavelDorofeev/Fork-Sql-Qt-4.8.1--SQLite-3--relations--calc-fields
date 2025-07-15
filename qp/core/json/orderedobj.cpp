#include "orderedobj.h"
#include <QDebug>

#include "my_json.h"
#include "pair.h"


OrderedObj::OrderedObj()
{

}

OrderedObj::OrderedObj( const QVariantMap &mmIn)
{
    fillFromQVariantMap( mmIn ) ;
}

void OrderedObj::fillFromQVariantMap( const QVariantMap &mmIn)
{
    //OrderedObj lst;

    QVariantMap::ConstIterator it = mmIn.constBegin();

    while (it != mmIn.constEnd())
    {
        const QVariant& var = *it;

        QString key = it.key();

        qDebug()<<" fillFromQVariantMap "<< key;

        lst.append( Pair2( key , var ) );

        it++;

    }

    //return *this;
}

QVariantMap OrderedObj::toQVariantMap( ) const
{
    QVariantMap mmOut;

    foreach ( const Pair2 &pp , lst)
    {
        qDebug() << pp.key << " ffdfsdfd ";

        const QString& key = pp.key;

        const QVariant& var = pp.val;

        mmOut.insert( key , var );

    }

    return mmOut;
}

void OrderedObj::toDebug( ) const
{
    bool ok;
    qDebug() << "--------------------- OrderedObj::toDebug( ) ------------------";
    foreach ( Pair2 pp , lst)
    {
        qDebug() << "    "<< pp.key<<" : " << QtJson::serialize1( pp.val );
    }
    qDebug() << "---------------------------------------------------------------";

}
