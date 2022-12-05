/****************************************************************************
**
** Contact: BIT Ltd Company (p@kkmspb.ru) Individual Taxpayer Number (ITN)  7826152874
**
** This file is not part of the Qt.
** This is a little fork of QSqlTableModel (Qt 4.8.1) version 3.0
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
**
**
****************************************************************************/

#include "pblsqlrecord.h"
#include "pblsqlrelationaltablemodel.h"
#include"qsqlrecord.h"

#include <QDebug>

class PblSqlRecordPrivate: public QSqlRecordPrivate
{
public:
    PblSqlRecordPrivate();
    //PblSqlRecordPrivate(const QSqlRecordPrivate &other);
private:


};

PblSqlRecordPrivate::PblSqlRecordPrivate():
    QSqlRecordPrivate()
{
    //qDebug() << "PblSqlRecordPrivate::PblSqlRecordPrivate";
}


PblSqlRecord::PblSqlRecord():
    QSqlRecord(), origСolCount(0)
{
    //qDebug("default ctor PblSqlRecord::PblSqlRecord this %p" , this);
}

PblSqlRecord::PblSqlRecord(const PblSqlRecord& other): // copy ctor
    QSqlRecord(other),
    origСolCount(other.origСolCount),
    exRelFieldsMap(other.exRelFieldsMap)
{
    //qDebug( "copy ctor PblSqlRecord(PblSqlRecord) this %p  exRelFieldsMap.count()=%i " , this  ,  exRelFieldsMap.count());

    //qDebug( "   copy ctor PblSqlRecord(PblSqlRecord) &other %p   other.exRelFieldsMap.count()=%i " ,  &other , other.exRelFieldsMap.count());
}

PblSqlRecord::PblSqlRecord(const QSqlRecord& other): // copy ctor
    QSqlRecord(other), origСolCount(0)
{
    //qDebug( "copy ctor PblSqlRecord(QSqlRecord&) this %p  &other %p exRelFieldsMap.count()=%i " , this , &other , exRelFieldsMap.count());
}

/*
PblSqlRecord& PblSqlRecord::operator=(const PblSqlRecord& other)
{
    qDebug( "operator = PblSqlRecord(PblSqlRecord) this %p  &other %p" , this , &other);
    qDebug()<< "other " <<other;
    Q_D(PblSqlRecord);
    qAtomicAssign(d, other.d);
    return *this;

    //return PblSqlRecord(other);
}*/

PblSqlRecord& PblSqlRecord::operator=(const QSqlRecord& other)
{
    //qDebug( "operator = PblSqlRecord(QSqlRecord) this %p  exRelFieldsMap.count()=%i " , this  , exRelFieldsMap.count());

    //qDebug( "   operator = PblSqlRecord(QSqlRecord) &other %p" ,  &other );

    return PblSqlRecord(other);
}

// protected:
PblSqlRecord::PblSqlRecord(const PblSqlRecordPrivate &dd)
    : QSqlRecord(dd)
{
    //qDebug() << "protected: PblSqlRecord::PblSqlRecord(const PblSqlRecordPrivate &dd)";
}

PblSqlRecord::~PblSqlRecord()
{
    //qDebug("dtor ~PblSqlRecord() this %p " , this );

    exRelFieldsMap.clear();

}

int PblSqlRecord::getRelIdCol(int origCol)
{
    if( ! exRelFieldsMap.contains(origCol))
    {
        qCritical() << "Error: PblSqlRecord not contains col : " << origCol;
        return -1;
    }
    else
        return exRelFieldsMap.value(origCol) + origСolCount;
}

void PblSqlRecord::appendExCol(int origCol , int exCol)
{
    exRelFieldsMap[origCol]= exCol;

}
