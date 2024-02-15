/****************************************************************************
**
** Contact: BIT Ltd Company (p@kkmspb.ru) Individual Taxpayer Number (ITN)  7826152874
**
** This file is not part of the Qt.
** This is a little convenient fork of QSqlTableModel (Qt 4.8.1) version 4.0
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

#include "qp_sqlrelation.h"
#include <QDebug>

int QpSqlRelation::counter = 0;

QpSqlRelation::QpSqlRelation()
    :
      extTblName("undefined"),
      ext_fld_name("")
{

    counter++;

    //qDebug() << "PblSqlRelation counter " << counter;

}

QpSqlRelation::QpSqlRelation( const QString & IdField1,
                                const QString & Table,
                                const QString & IdField2,
                                const QString & DestField,
                                JoinMode Join_mode)

    :

      idField1Name  ( IdField1),
      extTblName    ( Table),
      idField2Name  ( IdField2),
      dstFldName    ( DestField),
      // in table maybe exixts some relations to single external table
      ext_fld_name  ( QString("%1_%2_%3").arg(extTblName).arg(idField1Name).arg(idField2Name).replace(".","_") )
    // . (dot) may be appeare whan use ATTACH DATABASE

{
    joinMode = Join_mode;

    counter++;

    qDebug() << "PblSqlRelation counter " << counter << extTblName << idField1Name << idField2Name << dstFldName;

}

QString QpSqlRelation::get_fld_name()
{
    return idField1Name;
}

const QString & QpSqlRelation::get_ext_fld_name() const
{
    return ext_fld_name;
}


QpSqlRelation::~QpSqlRelation()
{
    counter--;

    //qDebug() << "~PblSqlRelation counter " << counter << extTblName << idField1Name << idField2Name << dstFldName;
}

QpSqlRelation QpSqlRelation::operator=(const QpSqlRelation &other)
{
    //qDebug() << "PblSqlRelation::operator=";

    //relation = other.relation;

    return *this;
};


