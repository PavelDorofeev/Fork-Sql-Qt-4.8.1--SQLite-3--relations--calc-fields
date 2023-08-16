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

#include "pblsqlrelation.h"
#include <QDebug>

int PblSqlRelation::counter = 0;

PblSqlRelation::PblSqlRelation()
    :
      extTblName("undefined"),
      ext_fld_name("")
{

    counter++;

    qDebug() << "PblSqlRelation counter " << counter;

}

PblSqlRelation::PblSqlRelation( const QString & IdField1,
                                const QString & Table,
                                const QString & IdField2,
                                const QString & DestField,
                                JoinMode Join_mode)

    :

      idField1Name  ( IdField1),
      extTblName    ( Table),
      idField2Name  ( IdField2),
      dstFldName    ( DestField),
      ext_fld_name  ( QString("%1_%2_%3") // in table maybe exixts some relations to single external table
                      .arg(extTblName)
                      .arg(idField1Name)
                      .arg(idField2Name) )

{
    joinMode = Join_mode;

    counter++;

    qDebug() << "PblSqlRelation counter " << counter << extTblName << idField1Name << idField2Name << dstFldName;

}

QString PblSqlRelation::get_fld_name()
{
    return idField1Name;
}

const QString & PblSqlRelation::get_ext_fld_name() const
{
    return ext_fld_name;
}


PblSqlRelation::~PblSqlRelation()
{
    counter--;

    qDebug() << "~PblSqlRelation counter " << counter << extTblName << idField1Name << idField2Name << dstFldName;
}

PblSqlRelation PblSqlRelation::operator=(const PblSqlRelation &other)
{
    qDebug() << "PblSqlRelation::operator=";

    //relation = other.relation;

    return *this;
};


