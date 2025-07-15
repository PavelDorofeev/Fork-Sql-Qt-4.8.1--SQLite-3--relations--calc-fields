#ifndef QHASHBUILDER_H
#define QHASHBUILDER_H
#include <QHash>
#include <QStringList>
#include <QDebug>

template <class T, class U>
class QHashBuilder
{
public:
    QHashBuilder & add(const T & key, const U & value)
    {
        if(hash.contains( key))
            qDebug()<<"QHashBuilder already has key:" << key; // sadfdsafdasfdsafd здесь было, не удалять

        //qDebug()<<"QHashBuilder key:" << key;
        // никогда здесь не используй - выводит в консоль !!!!
        //qWarning()<<"QHashBuilder key:" << key;

        hash.insert( key ,value );

        return *this;
    }

    inline QHashBuilder & addHash(const QStringList & lst)//<int,QString>
    {
        if( lst.isEmpty())
            return *this;

        for(int ii=0; ii<lst.count(); ii++)
        {
            bool ok;
            int kk = lst.at(ii).split(",").at(0).toInt( &ok);

            if( ! ok )
                continue;

            hash.insert( kk , lst.at(ii).split(",").at(1) );
        }

        return *this;
    }

    QHash<T,U> build()
    {
        return hash;
    }


private:
    QHash<T,U> hash;
};

#endif // QHASHBUILDER_H
