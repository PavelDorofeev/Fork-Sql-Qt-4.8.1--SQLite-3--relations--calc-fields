/******************************************************************************
**
** Contact: BIT Ltd Company (p@kkmspb.ru) Individual Taxpayer Number (ITN Russia) 7826152874
**
** This file is not part of the Qt Sources.
** This is a little convenient fork of QTableView (Qt 4.8.1) version 4.0
** created by Pavel Dorofeev ( p@kkmspb.ru )
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.

**                  Version 1.2
*******************************************************************************/

#ifndef QPMAP_H
#define QPMAP_H

#include <QMap>
#include <QVariantMap>
#include <QString>
#include <QStringList>  //!!!!!

//#include "qp/dll_qp_global.h" тут в шаблоне не надо
template <class Key, class T>
class QpMap : public QMap<Key,T>
{
public:
    QpMap():QMap<Key,T>(){};

    QpMap(const QMap<Key, T> &other): QMap<Key,T>(other){};
    

    // -----------------------------------------------------------------
    // addToMap добавляет в QVariantMap ключ/значение на любой уровень
    // вложенности дерева QVarinatMap
    // -----------------------------------------------------------------
    QVariantMap * findContainer( const QStringList &lst,
                                 bool createKey_IfNotExist =true,
                                 QVariant::Type type = QVariant::Map)
    {
        QVariantMap *pMap  = this;

        if(lst.count()==0)
            return this;

        int lvl=1;

        foreach( QString name , lst)
        {

            QVariantMap::Iterator it1 = pMap->find(name);

            if( it1 != pMap->constEnd()) // именно mmm->constEn...
            {
                // ---------------------------------------------------
                // если ключ СУЩЕСТВУЕТ получим ссылку на него в куче
                // ---------------------------------------------------

                if( it1.key() != name)
                {
                    return 0;
                }

                if( ! getMapPtr ( it1.value() , &pMap ) ) // переставляем указатель на следующий QVariantMap
                    return 0;

            }
            else if ( createKey_IfNotExist )
            {
                // -------------------------------------------
                // если ключ ЕЩЕ НЕ СУЩЕСТВУЕТ создадим его
                // -------------------------------------------

                pMap->insert( name, QpVariantMap() );

                //pMap->insert( name, new QpVariantMap() ); // можно и так

                QVariantMap::Iterator it2 = pMap->find(name);

                if( it2 != constEnd() && it2.key() == name)
                {
                    if( ! getMapPtr ( it2.value() , &pMap ) ) // переставляем указатель на следующий QVariantMap
                        return 0;
                }
                else
                {
                    return 0;
                }

            }
            else
            {
                return 0;
            }
        }

        return pMap;
    }

    bool addtoMap( const QStringList &lst,
                   const QString & key,// const Key & key,
                   const QVariant & val,
                   bool createKey_IfNotExist = true)
    {
        QVariantMap *pMap  = findContainer( lst , createKey_IfNotExist);

        if( pMap == 0 )
            return false;

        // на выходе устанавливаем ключ значение в контейнере дерева

        QVariantMap *map = reinterpret_cast<QVariantMap*>( pMap);

        //*mmm->insert(key, val); // ИЗМЕНИЛИ/ДОБАВИЛИ НОВЫЙ ЭЛЕМЕНТ !!!
        map->insert(key, val); //  странно но работает и так ????

        return true;
    }

    bool addtoList( const QStringList &lst,
                    const QString & lastListKey,
                    const QVariant & val,
                    bool createKey_IfNotExist = true)
    {

//        qDebug() << "addtoList val" << val;
//        qDebug() << "   lastListKey" << lastListKey;
//        qDebug() << "   lst" << lst << " lst.count() " << lst.count();
//        qDebug() << "   map" << *this;


        QVariantMap *pMap  = findContainer( lst , createKey_IfNotExist);

//        if( pMap != this )
//            qDebug() <<"sfadsadsfdasfd";

        if( pMap == 0 )
            return false;
        // на выходе устанавливаем ключ значение в контейнере дерева

        QVariantMap & mm =QVariantMap();

        if( ! pMap->contains(lastListKey ) )
        {
            pMap->insert( lastListKey, QVariantList() << val );
        }
        else
        {
            QVariantMap::Iterator it3 = pMap->find( lastListKey );

            if( it3 != pMap->constEnd()) // именно mmm->constEn...
            {
                // нашли

                QVariant &vv =  it3.value();

                if ( vv.userType() != QVariant::List )
                    return false;

                QVariantList * lst = reinterpret_cast<QVariantList*>(  it3.value().data()) ;
                lst->append( val);

                return true;
            }
            else
            {
                return 0;
            }

        }

        //qDebug() << "   map" << *this;
        return true;
    }

    bool getMapPtr( QVariant &var, QVariantMap **pMap)
    {
        // ---------------------------------------------------
        // приведение типа
        // ---------------------------------------------------

        if ( ! var.isValid() || var.userType() != QVariant::Map )
            return false;

        // проверили это  QVariantMap

        *pMap = reinterpret_cast<QVariantMap*>( var.data());

        return true;
    }

    bool getListPtr( QVariant &var, QVariantList **pLst)
    {
        // ---------------------------------------------------
        // приведение типа
        // ---------------------------------------------------

        if ( ! var.isValid() || var.userType() != QVariant::List )
            return false;

        // проверили это  QVariantList

        *pLst = reinterpret_cast<QVariantList*>( var.data());

        return true;
    }


};

typedef QpMap<QString,QVariant> QpVariantMap ;

#endif // QPMAP_H
