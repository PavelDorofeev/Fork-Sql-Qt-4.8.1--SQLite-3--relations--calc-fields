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

#ifndef PBLSQLRECORD_H
#define PBLSQLRECORD_H

#include <QSqlRecord>
#include <QMap>
#include <QDebug>

class PblSqlRelationalTableModel;

class PblSqlRecordPrivate;

class Q_SQL_EXPORT PblSqlRecord: public QSqlRecord
{

public:

    PblSqlRecord();

    PblSqlRecord(const PblSqlRecord& other);    // конструктор копирования стандартный

    // для функции record

    PblSqlRecord(const QSqlRecord& other);      // конструктор копирования не стандартный
    //(копирование от предка)


    //PblSqlRecord& operator=(const PblSqlRecord& other);
    PblSqlRecord& operator=(const QSqlRecord& other);

    ~PblSqlRecord();

    int origСolCount;

    int getRelIdCol(int origCol);

    void appendExCol(int origCol , int exCol);

    int getRef();
public:
    QHash<int,int> exRelFieldsMap;


protected:

    PblSqlRecord(const PblSqlRecordPrivate &dd);

private:

    //Q_DECLARE_PRIVATE(PblSqlRecord)
    //PblSqlRecordPrivate* d;


};

#endif // PBLSQLRECORD_H
